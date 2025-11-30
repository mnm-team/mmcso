import os
import re
import math
import matplotlib.pyplot as plt
import pandas as pd

linestyles = { True: ':', False: '-.' }

colors = ['darkorange', 'darkgreen', 'mediumvioletred', 'darkblue', 'orange', 'red', 'yellow', 'violet']

colors_by_num_threads = {
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

def plot_overhead(df, row, fig, ax, mpi):
    df['comm_time'] = (df['comm_time'] - df['comp_time']) / df['rep'] * 1.0e6
    # df['comm_time'] = (df['wait_time']) / df['rep'] * 1.0e6
    # df['comm_time'] = (df['wait_time'] + df['post_time']) / df['rep'] * 1.0e6
    # df['comm_time'] = (df['post_time']) / df['rep'] * 1.0e6

    """
    # for ax in fig.get_axes():
    #    ax.label_outer()
    fig.suptitle(f'Spinlocks (48 Core ARM A64FX) N={n}')
    """
    
def get_rank(filename):
    match = re.search(r"hawk-r(\d+)\.mt-(\d+)-(\d+)-.*\.csv", filename)
    if match:
        return int(match.group(1))
    else:
        print(filename + ": No match found")
        exit()
    
def make_dataframe(csv_files):
    dfs = []
    for f in csv_files:
        df = pd.read_csv(f)
        offload = False if '_native' in f else True
        df['offload'] = offload
        dfs = dfs + [df]
    df_concat = pd.concat(dfs, ignore_index=True)
    # print(df_concat)
    return df_concat

def plot_speedup(df, ax, title, is_mem):

    ax.hlines(y=1.0, xmin=df['msg_size'].min(), xmax=df['msg_size'].max(), color='darkgrey')
    df_offload = df['offload'] == True
    
    # merge dfs to compute speedup
    df = pd.merge(df.loc[~df_offload], df.loc[df_offload], on=('msg_size', 'work'), suffixes=('_native', '_offload'))
    df['speedup'] = df['comm_time_native'] / df['comm_time_offload']
    
    if is_mem:
        df = df[(df['work'] == 500) | (df['work'] == 5000) | (df['work'] == 50000) | (df['work'] == 500000)]
    else:
        df = df[(df['work'] == 100) | (df['work'] == 1000) | (df['work'] == 10000) | (df['work'] == 100000)]
    
    dfg = df.groupby(['work'])
    
    for i, ((w), gp) in enumerate(dfg):
        line = gp.plot(ax=ax, x='msg_size', y='speedup', logx=True, logy=False, color=colors[i], linestyle='-.' if is_mem else ':', 
                       marker='^' if is_mem else 'o', markerfacecolor='none', markersize=8)
                       #, yerr='std', elinewidth=0.1, capsize=3, capthick=0.1)
    
    legend_labels = []
    
    if is_mem:
        legend_labels = [f"{10*work//1000} kbytes" for work in dfg.groups]
        ax.set_ylabel('Speedup (memcpy)')
    else:
        # ax.set_title(title)
        legend_labels = [f"{work} ns" for work in dfg.groups]
        ax.set_ylabel('Speedup')
        
    ax.legend(handles=ax.get_legend().legend_handles[0:], labels=legend_labels,
                                 loc='best',
                                 ncol=1,
                                 labelspacing=0.5,
                                 markerscale=1.5,
                                 frameon=True,
                                 framealpha=0.8,
                                 title=f"Work ({'memcpy' if is_mem else 'sleep'})"
                                 )
    
def plot(axs, df, is_mem):
    
    conf1 = ('2-4', '1 MPI proc per Socket, 63 threads per MPI proc')
    conf2 = ('2-8', '2 MPI proc per Socket, 31 threads per MPI proc')
    conf3 = ('2-16', '1 MPI proc per NUMA domain, 15 threads per MPI proc')
    conf4 = ('2-4', '1 MPI proc per Socket, 23 threads per MPI proc')
    
    configs = [conf4]
    
    ymax = 3.5
    # ymax = 17.5
    ytickmax = math.ceil(ymax)
    
    # data frames for non-memory-intensive work
    for i, (conf, title) in enumerate(configs):
        # df = df[(df['work'] == 100) | (df['work'] == 1000) | (df['work'] == 10000) | (df['work'] == 100000)]
        df = df.groupby(['nthreads', 'msg_size', 'offload', 'work']).mean().drop(['rank', 'thread'], axis=1).reset_index()
        plot_speedup(df, axs, title, is_mem)
    
    axs.grid(alpha=0.3)
    axs.set_xlim(2, 1.0e9)
    axs.set_xlabel('Message Size [bytes]')
    # axs.set_ylabel('speedup')
    axs.set_yticks(range(ytickmax))
    axs.set_ylim(0.5, ymax)
    # axs.legend().set_visible(False)
        
    # axs[1].legend().set_visible(False)

if __name__ == '__main__':

    # fig, axs = plt.subplots(2, 1, figsize=(16, 9), sharex=True, sharey=True)
    fig, axs = plt.subplots(1, 2, figsize=(16, 5), sharex=True, sharey=True)

    # csv_files = [f for f in os.listdir('.') if os.path.isfile(f) and f.endswith('.csv')]
    csv_files_compute = ['./result/inter_native_compute_2nodes_4procs.csv', 
                         './result/inter_offload_compute_2nodes_4procs.csv']
    csv_files_mem = ['./result/inter_native_mem_2nodes_4procs.csv', 
                     './result/inter_offload_mem_2nodes_4procs.csv']
    config = ('2-4', '1 MPI proc per Socket, 23 threads per MPI proc')
    df_compute = make_dataframe(csv_files_compute)
    df_mem = make_dataframe(csv_files_mem)
    plot(axs[0], df_compute, False)
    plot(axs[1], df_mem, True)
    
    fig.suptitle(f'SNG: Intel Xeon(R) Gold 6148 48 Cores \n(2 Nodes, 1 MPI proc per Socket, 23 threads per MPI proc)')
    
    plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=0.5)
    plt.subplots_adjust(top=0.90)
    plt.savefig(f'./speedup_microbench_sng.pdf')
    print("Saved figure to ./speedup_microbench_sng.pdf")
    
    # plt.show()