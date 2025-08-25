import itertools
import matplotlib.pyplot as plt
import pandas as pd

# linestyles = itertools.cycle(['--', '-.', ':'])
# linestyles = itertools.cycle(['-.'])
# markers = itertools.cycle("ov+.*^")

linestyles = { True: ':', False: '-.' }

colors = {
    (100, True): 'darkorange',
    (100, False): 'orange',
    # 8: 'forestgreen',
    (10000, True): 'darkgreen',
    (10000, False): 'forestgreen',
    # 16: 'blue',
    (1000000, True): 'mediumvioletred',
    (1000000, False): 'violet'
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
    ax.set_ylim(bottom=bottom) #, top=220.0)
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
        gp.plot(ax=ax[coord[w], col], x='msg_size', y='overlap', logx=True, logy=False, color=colors[t,o], linestyle=linestyles[o]
        , marker=markers[o], markerfacecolor='none', markersize=8)#, yerr='std', elinewidth=0.1, capsize=3, capthick=0.1)

    set_axis(ax[(0,col)], True, 'avg. overlap [%]', 0)
    set_axis(ax[(1,col)], False, 'avg. overlap [%]', 0)
    set_axis(ax[(2,col)], False, 'avg. overlap [%]', 0)

    for wrk in coord:
        if wrk == 100:
            ax[coord[wrk], col].set_title(f'{mpi}\nwork: {wrk} ns')
        else:
            ax[coord[wrk], col].set_title(f'work: {wrk} ns')

    # legend_labels = [f"{type}" for (type) in df_mean.groupby(['nthreads', 'offload']).groups]
    legend_labels = [f"{type[0]} Threads {'(Offloading)' if type[1] else ''}" for (type) in df_mean.groupby(['nthreads', 'offload']).groups]

    ax[(0,0)].legend(legend_labels,
                                 loc='upper right',
                                #  bbox_to_anchor=(0.5, 1.05),
                                 ncol=1,
                                 labelspacing=0.5,
                                 markerscale=1.5,
                                 frameon=True,
                                 framealpha=0.8,
                                 title="Threads per Process   /   Offloading"
                                 )

if __name__ == '__main__':

    fig, ax = plt.subplots(1, 2, figsize=(16, 9), sharex=True, sharey=True)

    # for intra-inter-node communication
    prefix = '../experiments/intra_inter_node_comm/result/'

    # for the 1st figure
    df_intra_offload = pd.read_csv(prefix + "offload_intra_node.csv")
    df_intra_native = pd.read_csv(prefix + "native_intra_node.csv")
    df_intra_offload['offload'] = True
    df_intra_native['offload'] = False
    df_intra_comm = pd.concat([df_intra_offload, df_intra_native])

    plot_overlap(df_intra_comm, 0, fig, ax, 'IntelMPI')

    # for the 2nd figure
    df_inter_offload = pd.read_csv(prefix + "offload_inter_node.csv")
    df_inter_native = pd.read_csv(prefix + "native_inter_node.csv")
    df_inter_offload['offload'] = True
    df_inter_native['offload'] = False
    df_inter_comm = pd.concat([df_inter_offload, df_inter_native])

    plot_overlap(df_inter_comm, 1, fig, ax, 'OpenMPI')
    # plot_overhead(df, 0)
    # for n in df['work'].unique():
        # plot(df, n)

    ax[0,1].legend().set_visible(False)
    
    # fig.suptitle(f'Intel Xeon Platinum 8174 (SuperMUC Skylake) 48 Core CPU (single node)')

    # plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=0.5)
    # plt.subplots_adjust(top=0.90)
    plt.savefig(f'overlap_intra_inter_node_comm.pdf')

