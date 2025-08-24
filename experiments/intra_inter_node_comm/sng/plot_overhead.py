import os
import re
import math
import matplotlib.pyplot as plt
import pandas as pd

linestyles = { True: ':', False: '-.' }

colors = ['darkorange', 'darkgreen', 'mediumvioletred', 'darkblue', 'orange', 'red', 'yellow', 'violet']

colors_by_comm = {
    # (intra, offload)
    (False, False): 'darkorange',
    (False, True): 'orange',
    # (inter, offload)
    (True, False): 'darkgreen',
    (True, True): 'forestgreen',
    # 16: 'blue',
    # (23, True): 'mediumvioletred',
    # (23, False): 'violet'
}

markers = {
    True: 'o',
    False: '^'
}

def plot_overhead(df, ax, is_mem):
    # df['comm_time'] = (df['comm_time'] - df['comp_time']) / df['rep'] * 1.0e6
    # df['comm_time'] = (df['wait_time']) / df['rep'] * 1.0e6
    # df['comm_time'] = (df['wait_time'] + df['post_time']) / df['rep'] * 1.0e6
    df['comm_time'] = (df['post_time']) / df['rep'] * 1.0e6

    df = df[(df['work'] == 100)] # | (df['work'] == 10000) # | (df['work'] == 1000000)]

    df_mean = df.groupby(['inter', 'work', 'msg_size', 'offload', 'nthreads']).max().reset_index()
    df_std = df.groupby(['inter', 'work', 'msg_size', 'offload', 'nthreads']).std().reset_index()
    df_mean['std'] = df_std['comm_time']

    dfg = df_mean.groupby(['inter', 'work', 'offload', 'nthreads'])
    for (i, w, o, t), gp in dfg:
        # print(f'inter: {i}, works: {w} , offload: {o}')
        gp.plot(ax=ax, x='msg_size', y='comm_time', logx=True, logy=True, color=colors_by_comm[i,o], linestyle=linestyles[o],
                marker=markers[o], markerfacecolor='none', markersize=8)
                #, yerr='std', elinewidth=0.1, capsize=3, capthick=0.1)

    legend_labels = [f"{'Inter-Comm'if type[0] else 'Intra-Comm'} {'\n(Offloading)' if type[1] else '\n(Native)'}" for (type) in df_mean.groupby(['inter', 'offload']).groups]

    ax.legend(legend_labels,
                                loc='upper left',
                                ncol=3,
                                labelspacing=0.5,
                                markerscale=1.5,
                                frameon=True,
                                framealpha=0.8,
                                title="Workload (100ns sleep)"
                                )
    
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
        inter = False if 'intra_' in f else True
        df['inter'] = inter
        offload = False if '_native' in f else True
        df['offload'] = offload
        dfs = dfs + [df]
    df_concat = pd.concat(dfs, ignore_index=True)
    
    return df_concat

def make_dataframe_hawk(csv_files, conf, mem, data_dir, inter):
    if mem:
        conf = conf + '-mem-'
        
    csv_files = [f for f in csv_files if conf in f]
    # print(f'Files for conf {conf}: {csv_files}')
    dfs = []
    
    for f in csv_files:
        df = pd.read_csv(os.path.join(data_dir + '/' + f))
        rank = get_rank(os.path.join(data_dir + '/' + f))
        offload = False if '-default' in f else True
        df['rank'] = rank
        df['inter'] = inter
        df['offload'] = offload
        dfs = dfs + [df]

    ret_df = pd.concat(dfs, ignore_index=True)
        
    return ret_df

if __name__ == '__main__':

    # fig, axs = plt.subplots(1, 2, figsize=(16, 9), sharex=True, sharey=True)
    fig, axs = plt.subplots(1, 2, figsize=(16, 5), sharex=True, sharey=True)


    # ----------------------------------
    # SNG data and plot
    # ----------------------------------
    # csv_files = [f for f in os.listdir('.') if os.path.isfile(f) and f.endswith('.csv')]
    csv_files_compute = ['./result/intra_native_compute_1node_2procs.csv',
                         './result/intra_offload_compute_1node_2procs.csv',
                         './result/inter_native_compute_2nodes_4procs.csv', 
                         './result/inter_offload_compute_2nodes_4procs.csv']
    csv_files_mem = ['./result/inter_native_mem_2nodes_4procs.csv', 
                     './result/inter_offload_mem_2nodes_4procs.csv']
    config = ('2-4', '1 MPI proc per Socket, 23 threads per MPI proc')
    df_compute_intra_inter = make_dataframe(csv_files_compute)
    plot_overhead(df_compute_intra_inter, axs[0], False)
    
    # fig.suptitle(f'Overhead on SNG: Intra- and Inter-Node Communication')

    # ----------------------------------
    # HAWK data and plot
    # ----------------------------------
    # hawk_data_dir = '../hawk'
    # hawk_csv_files = [f for f in os.listdir(hawk_data_dir) if f.endswith('.csv')]
    # conf1 = ('2-4', '1 MPI proc per Socket, 63 threads per MPI proc')
    # conf2 = ('2-8', '2 MPI proc per Socket, 31 threads per MPI proc')
    # conf3 = ('2-16', '1 MPI proc per NUMA domain, 15 threads per MPI proc')
    # hawk_df_compute_intra = make_dataframe_hawk(hawk_csv_files, conf3[0], False, hawk_data_dir, False)
    # hawk_df_compute_inter = make_dataframe_hawk(hawk_csv_files, conf1[0], False, hawk_data_dir, True)
    # hwak_df_compute = pd.concat([hawk_df_compute_intra, hawk_df_compute_inter], ignore_index=True)
    # plot_overhead(hwak_df_compute, axs[1], False)
    
    plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=0.5)
    plt.subplots_adjust(top=0.90)
    plt.savefig(f'./overhead_microbench_sng.pdf')
    print("Saved figure to ./overhead_microbench_sng.pdf")
