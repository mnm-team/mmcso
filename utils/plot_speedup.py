import itertools
import matplotlib.pyplot as plt
import pandas as pd

# linestyles = itertools.cycle(['--', '-.', ':'])
# linestyles = itertools.cycle(['-.'])
# markers = itertools.cycle("ov+.*^")

linestyles = { True: ':', False: '-.' }

colors = {
    (2, True): 'darkorange',
    (2, False): 'orange',
    # 8: 'forestgreen',
    (12, True): 'darkgreen',
    (12, False): 'forestgreen',
    # 16: 'blue',
    (23, True): 'mediumvioletred',
    (23, False): 'violet'
}

markers = {
    True: 'o',
    False: '^'
}

coord = {
    100: 0,
    # 1000: (0, 1),
    10000: 1,
    # 100000: (1, 1),
    1000000: 2
}

def set_axis(ax, legend, ylabel,bottom):
    ax.set_ylim(bottom=bottom, top=4) #, top=220.0)
    ax.set_xlabel('msg size [bytes]')
    ax.set_ylabel(ylabel)
    # ax.set_ylabel('avg. communication overhead per msg [µs]')
    ax.legend().set_visible(legend)
    ax.grid(alpha=0.3)

def plot_overlap(df, col, fig, ax, mpi):
    

    df['overlap'] = (df['comp_time'] / df['comm_time']) * 100

    # df = df[df['nthreads'] == n]
    df = df[(df['work'] == 100) | (df['work'] == 10000) | (df['work'] == 1000000)]
    # 0 1 10 100 1000 10000 100000

    df = df[(df['nthreads'] == 2) | (df['nthreads'] == 12) | (df['nthreads'] == 23)]

    df_mean = df.groupby(['nthreads', 'msg_size', 'offload', 'work']).mean().reset_index()
    df_std = df.groupby(['nthreads', 'msg_size', 'offload', 'work']).std().reset_index()

    df_mean['std'] = df_std['overlap']

    dfg = df_mean.groupby(['nthreads', 'offload', 'work'])

    for (t, o, w), gp in dfg:
        print(f'threads: {t} , offload: {o}')
        gp.plot(ax=ax[coord[w]], x='msg_size', y='speedup', logx=True, logy=False, color=colors[t,o], linestyle=linestyles[o]
        , marker=markers[o], markerfacecolor='none', markersize=8)#, yerr='std', elinewidth=0.1, capsize=3, capthick=0.1)

    set_axis(ax[(0)], True, 'Speedup', 0)
    set_axis(ax[(1)], False, 'Speedup', 0)
    set_axis(ax[(2)], False, 'Speedup', 0)

    for wrk in coord:
        if wrk == 100:
            ax[coord[wrk]].set_title(f'{mpi}\nwork: {wrk} ns')
        else:
            ax[coord[wrk]].set_title(f'work: {wrk} ns')

    # legend_labels = [f"{type}" for (type) in df_mean.groupby(['nthreads', 'offload']).groups]
    legend_labels = [f"{type[0]} Threads" for (type) in df_mean.groupby(['nthreads', 'offload']).groups]

    ax[(0)].legend(legend_labels,
                                 loc='upper right',
                                #  bbox_to_anchor=(0.5, 1.05),
                                 ncol=1,
                                 labelspacing=0.5,
                                 markerscale=1.5,
                                 frameon=True,
                                 framealpha=0.8,
                                 title="Threads per Process"
                                 )

if __name__ == '__main__':

    fig, ax = plt.subplots(3, 1, figsize=(9, 9), sharex=True, sharey=True)

    prefix = 'intelmpi-1node/'
    # prefix = 'intelmpi-2node/'

    df1 = pd.read_csv(prefix + "offload.csv")
    df2 = pd.read_csv(prefix + "native.csv")
    df1['offload'] = True
    df2['offload'] = False
    #df = df1.append(df2)
    #df = pd.concat([df1, df2])
    df1['speedup'] = df2['comm_time'] / df1['comm_time']

    plot_overlap(df1, 0, fig, ax, 'IntelMPI')

    prefix = 'openmpi-1node/'
    # prefix = 'openmpi-2node/'

    df1 = pd.read_csv(prefix + "offload.csv")
    df2 = pd.read_csv(prefix + "native.csv")
    df1['offload'] = True
    df2['offload'] = False
    #df = df1.append(df2)
    df = pd.concat([df1, df2])
    df1['speedup'] = df2['comm_time'] / df1['comm_time']

    # plot_overlap(df1, 1, fig, ax, 'OpenMPI')
    # plot_overhead(df, 0)
    # for n in df['work'].unique():
        # plot(df, n)

    #ax[0,1].legend().set_visible(False)
    
    fig.suptitle(f'Intel Xeon Platinum 8174 (SuperMUC Skylake) 48 Core CPU (single node)')

    #plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=0.5)
    #plt.subplots_adjust(top=0.90)
    plt.savefig(f'commoff_speedup_1n.png') #, tight_layout=True)

