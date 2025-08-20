import itertools
import matplotlib.pyplot as plt
import pandas as pd

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
    0: (0, 0),
    1: (0, 1),
    # 1000: (0, 1),
    10000: (1, 0),
    # 100000: (1, 1),
    1000000: (1, 1)
}

def set_axis(ax, legend, ylabel,bottom):
    ax.set_ylim(bottom=bottom) #, top=220.0)
    ax.set_xlabel('msg size [bytes]')
    ax.set_ylabel(ylabel)
    # ax.set_ylabel('avg. communication overhead per msg [µs]')
    ax.legend().set_visible(legend)
    ax.grid(alpha=0.3)

def plot_overhead(df, row, fig, ax, mpi):
    df['comm_time'] = (df['comm_time'] - df['comp_time']) / df['rep'] * 1.0e6
    # df['comm_time'] = (df['wait_time']) / df['rep'] * 1.0e6
    # df['comm_time'] = (df['wait_time'] + df['post_time']) / df['rep'] * 1.0e6
    # df['comm_time'] = (df['post_time']) / df['rep'] * 1.0e6

    # df = df[df['nthreads'] == n]
    df = df[(df['work'] == 0)]
    # 0 1 10 100 1000 10000 100000

    df = df[(df['nthreads'] == 2) | (df['nthreads'] == 12) | (df['nthreads'] == 23)]

    df_mean = df.groupby(['nthreads', 'msg_size', 'offload', 'work']).mean().reset_index()
    df_std = df.groupby(['nthreads', 'msg_size', 'offload', 'work']).std().reset_index()

    df_mean['std'] = df_std['comm_time']

    dfg = df_mean.groupby(['nthreads', 'offload', 'work'])

    for (t, o, w), gp in dfg:
        print(f'threads: {t} , offload: {o}')
        gp.plot(ax=ax[row], x='msg_size', y='comm_time', logx=True, logy=True, color=colors[t,o], linestyle=linestyles[o]
        , marker=markers[o], markerfacecolor='none', markersize=8)#, yerr='std', elinewidth=0.1, capsize=3, capthick=0.1)

    set_axis(ax[row], True, 'avg. communication overhead [us]', 1)
    # set_axis(ax[(0,1)], False, 'avg. communication overhead per iter [µs]', 1)
    # set_axis(ax[(1,0)], False, 'avg. communication overhead per iter [µs]', 1)
    # set_axis(ax[(1,1)], False, 'avg. communication overhead per iter [µs]', 1)

    # for wrk in coord:
    ax[row].set_title(f'{mpi} (zero work)')

    # legend_labels = [f"{type} {type[0]}" for (type) in df_mean.groupby(['nthreads', 'offload']).groups]
    legend_labels = [f"{type[0]} Threads {'(Offloading)' if type[1] else ''}" for (type) in df_mean.groupby(['nthreads', 'offload']).groups]

    ax[0].legend(legend_labels,
                                 loc='best',
                                 ncol=3,
                                 labelspacing=0.5,
                                 markerscale=1.5,
                                 frameon=True,
                                 framealpha=0.8,
                                 title="Threads per Process   /   Offloading"
                                 )

    # plt.show()

    """
    # for ax in fig.get_axes():
    #    ax.label_outer()
    fig.suptitle(f'Spinlocks (48 Core ARM A64FX) N={n}')
    """

if __name__ == '__main__':

    fig, ax = plt.subplots(1, 2, figsize=(16, 9), sharex=True, sharey=True)

    prefix = 'intelmpi-1node/'
    # prefix = 'intelmpi-2node/'

    df1 = pd.read_csv(prefix + "offload.csv")
    df2 = pd.read_csv(prefix + "native.csv")
    df1['offload'] = True
    df2['offload'] = False
    #df = df1.append(df2)
    df = pd.concat([df1, df2])

    plot_overhead(df, 0, fig, ax, 'IntelMPI')

    prefix = 'openmpi-1node/'
    # prefix = 'openmpi-2node/'

    df1 = pd.read_csv(prefix + "offload.csv")
    df2 = pd.read_csv(prefix + "native.csv")
    df1['offload'] = True
    df2['offload'] = False
    #df = df1.append(df2)
    df = pd.concat([df1, df2])

    plot_overhead(df, 1, fig, ax, 'OpenMPI')
    # plot_overhead(df, 0)
    # for n in df['work'].unique():
        # plot(df, n)

    ax[1].legend().set_visible(False)
    
    fig.suptitle(f'Intel Xeon Platinum 8174 (SuperMUC Skylake) 48 Core CPU (single node)')

    plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=0.5)
    plt.subplots_adjust(top=0.90)
    plt.savefig(f'commoff_overhead.pdf')
