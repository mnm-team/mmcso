import itertools
import matplotlib.pyplot as plt
import pandas as pd

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
    0: (0, 0),
    1: (0, 1),
    # 1000: (0, 1),
    10000: (1, 0),
    # 100000: (1, 1),
    1000000: (1, 1)
}

def set_axis(ax, legend, ylabel,bottom):
    ax.set_ylim(bottom=bottom)
    ax.set_xlabel('msg size [bytes]')
    ax.set_ylabel(ylabel)
    # ax.set_ylabel('avg. communication overhead per msg [µs]')
    ax.legend().set_visible(legend)
    ax.grid(alpha=0.3)

def plot_overhead(df, row, fig, ax, mpi):
    # df['comm_time'] = (df['comm_time'] - df['comp_time']) / df['rep'] * 1.0e6
    # df['comm_time'] = (df['wait_time']) / df['rep'] * 1.0e6
    # df['comm_time'] = (df['wait_time'] + df['post_time']) / df['rep'] * 1.0e6
    df['comm_time'] = (df['post_time']) / df['rep'] * 1.0e6

    # df = df[df['nthreads'] == 23]
    # df = df[(df['work'] == 0)]
    # 0 1 10 100 1000 10000 100000

    df = df[(df['work'] == 100)] # | (df['work'] == 10000) # | (df['work'] == 1000000)]

    df_mean = df.groupby(['work', 'msg_size', 'offload', 'nthreads']).max().reset_index()
    df_std = df.groupby(['work', 'msg_size', 'offload', 'nthreads']).std().reset_index()
    df_mean['std'] = df_std['comm_time']

    dfg = df_mean.groupby(['work', 'offload', 'nthreads'])
    for (w, o, t), gp in dfg:
        print(f'works: {w} , offload: {o}')
        gp.plot(ax=ax[row], x='msg_size', y='comm_time', logx=True, logy=True, color=colors[w,o], linestyle=linestyles[o],
                marker=markers[o], markerfacecolor='none', markersize=8)
                #, yerr='std', elinewidth=0.1, capsize=3, capthick=0.1)

    set_axis(ax[row], True, 'avg. communication overhead [us]', 1)
    # set_axis(ax[(0,1)], False, 'avg. communication overhead per iter [µs]', 1)
    # set_axis(ax[(1,0)], False, 'avg. communication overhead per iter [µs]', 1)
    # set_axis(ax[(1,1)], False, 'avg. communication overhead per iter [µs]', 1)

    # for wrk in coord:
    ax[row].set_title(f'{mpi}')

    # legend_labels = [f"{type} {type[0]}" for (type) in df_mean.groupby(['nthreads', 'offload']).groups]
    legend_labels = [f"{type[0]} (ns) {'\n(Offloading)' if type[1] else ''}" for (type) in df_mean.groupby(['work', 'offload']).groups]

    ax[row].legend(legend_labels,
                                 loc='upper left',
                                 ncol=3,
                                 labelspacing=0.5,
                                 markerscale=1.5,
                                 frameon=True,
                                 framealpha=0.8,
                                 title="Workload"
                                 )

    # plt.show()

    """
    # for ax in fig.get_axes():
    #    ax.label_outer()
    fig.suptitle(f'Spinlocks (48 Core ARM A64FX) N={n}')
    """

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
    # print(df_intra_comm)
    plot_overhead(df_intra_comm, 0, fig, ax, 'Intel-MPI Intra-Node Comm. on SNG (single node)')

    # for the 2nd figure
    df_inter_offload = pd.read_csv(prefix + "offload_inter_node.csv")
    df_inter_native = pd.read_csv(prefix + "native_inter_node.csv")
    df_inter_offload['offload'] = True
    df_inter_native['offload'] = False
    df_inter_comm = pd.concat([df_inter_offload, df_inter_native])
    plot_overhead(df_inter_comm, 1, fig, ax, 'Intel-MPI Inter-Node Comm. on SNG (2 nodes)')

    # ax[1].legend().set_visible(False)

    # fig.suptitle(f'Intel Xeon Platinum 8174 (SuperMUC Skylake) 48 Core CPU (Single Node)')

    # plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=0.5)
    # plt.subplots_adjust(top=0.90)
    plt.savefig(f'overhead_intra_inter_node_comm.pdf')
