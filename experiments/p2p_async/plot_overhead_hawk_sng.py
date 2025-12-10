import os
import re
import matplotlib.pyplot as plt
import pandas as pd

linestyles = { 'offload': ':', 'native': '-.', 'async': 'dashed' }

colors_by_comm = {
    # (conf, mode)
    (3, 'native'): 'darkgreen',
    (3, 'offload'): 'red',
    (1, 'native'): 'darkorange',
    (1, 'offload'): 'darkblue',
    (1, 'async'): 'grey',
}

markers = {
    'offload': '*',
    'native': '^',
    'async': 'x'
}

def plot_overhead(df, ax, kind, is_sng, title):
    # df['comm_time'] = (df['comm_time'] - df['comp_time']) / df['rep'] * 1.0e6
    if kind == 'post':
        df['comm_time'] = (df['post_time']) / df['rep'] * 1.0e6
    elif kind == 'wait':
        df['comm_time'] = (df['wait_time']) / df['rep'] * 1.0e6
    else:
        KeyError
    
    # df['comm_time'] = (df['wait_time'] + df['post_time']) / df['rep'] * 1.0e6

    df = df[(df['work'] == 100)]
    
    print('SNG' if is_sng else 'HAWK')
    # print(df.head())

    df_mean = df.groupby(['conf', 'mode', 'work', 'msg_size', 'nthreads']).mean().reset_index()
    df_std = df.groupby(['conf', 'mode', 'work', 'msg_size', 'nthreads']).std().reset_index()
    df_mean['std'] = df_std['comm_time']
    
    dfg = df_mean.groupby(['conf', 'mode', 'work', 'nthreads'])
    
    # sort such that async is plotted last
    li = list(dfg)
    if is_sng:
        li = [li[1], li[2], li[0]]
    
    # print(li[0])
    
    for (c, m, w, t), gp in li:
        label='1 MPI proc per socket' if c == 1 else '1 MPI proc per NUMA domain'
        label=f'{label}\n({m.capitalize()})'
        gp.plot(ax=ax, x='msg_size', y='comm_time', logx=True, logy=True, color=colors_by_comm[c, m], linestyle=linestyles[m],
                marker=markers[m], markerfacecolor='none', markersize=8,
                label=label)
                #, yerr='std', elinewidth=0.1, capsize=3, capthick=0.1)

    if is_sng:
        ncol=1
    else:
        ncol=2

    ax.legend(#legend_labels,
                loc='upper left',
                ncol=ncol,
                labelspacing=0.5,
                markerscale=1.5,
                frameon=True,
                framealpha=0.8,
                title="Workload (100ns sleep)"
                )
    ax.set_xlabel('Message Size [bytes]')
    ax.grid(True)
    ax.set_title(title) # fontsize = 14)
    
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
        if 'split-async' in f:
            df['mode'] = 'split-async'
        elif 'async' in f:
            df['mode'] = 'async'
        elif 'offload' in f:
            df['mode'] = 'offload'
        elif 'split-default' in f:
            df['mode'] = 'split'
        else:
            df['mode'] = 'native'
        # offload = False if '_native' in f else True
        # df['offload'] = offload
        df['conf'] = 1
        dfs = dfs + [df]
    df_concat = pd.concat(dfs, ignore_index=True)
    # print(df_concat)
    
    return df_concat

def make_dataframe_hawk(csv_files, conf, mem, data_dir, inter):
    if mem:
        conf = conf + '-mem-'
        
    csv_files = [f for f in csv_files if conf in f]
    print(f'Files for conf {conf}: {csv_files}')
    dfs = []
    
    for f in csv_files:
        df = pd.read_csv(os.path.join(data_dir + '/' + f))
        rank = get_rank(os.path.join(data_dir + '/' + f))

        df['rank'] = rank
        df['conf'] = 1 if '2-4' in f else 3
        df['mode'] = 'native' if '-default' in f else 'offload'
        dfs = dfs + [df]

    ret_df = pd.concat(dfs, ignore_index=True)
        
    return ret_df

if __name__ == '__main__':

    # fig, axs = plt.subplots(1, 2, figsize=(16, 9), sharex=True, sharey=True)
    fig, axs = plt.subplots(1, 2, figsize=(16, 4), sharex=True, sharey=True)

    # ----------------------------------
    # HAWK data and plot
    # ----------------------------------
    hawk_data_dir = './hawk/result'
    hawk_csv_files = [f for f in os.listdir(hawk_data_dir) if f.endswith('.csv')]
    conf1 = ('2-4', '1 MPI proc per Socket, 63 threads per MPI proc')
    conf2 = ('2-8', '2 MPI proc per Socket, 31 threads per MPI proc')
    conf3 = ('2-16', '1 MPI proc per NUMA domain, 15 threads per MPI proc')
    hawk_df_compute_c3 = make_dataframe_hawk(hawk_csv_files, conf3[0], False, hawk_data_dir, False)
    hawk_df_compute_c1 = make_dataframe_hawk(hawk_csv_files, conf1[0], False, hawk_data_dir, True)
    hwak_df_compute = pd.concat([hawk_df_compute_c3, hawk_df_compute_c1], ignore_index=True)
    
    ## WAIT FIGURE
    
    subtitle_hawk = f'Wait Time on Hawk'
    plot_overhead(hwak_df_compute, axs[0], 'wait', False, subtitle_hawk)

    # ----------------------------------
    # SNG data and plot
    # ----------------------------------
    sng_data_dir = './sng/result'
    csv_files_compute = [
                         sng_data_dir + '/sng-2-4-async.csv', 
                         sng_data_dir + '/sng-2-4-default.csv',
                         sng_data_dir + '/sng-2-4-offload.csv'
                         ]
    
    config = ('2-4', '1 MPI proc per Socket, 23 threads per MPI proc')
    df = make_dataframe(csv_files_compute)
    
    subtitle_sng = f'Wait Time on SNG'
    plot_overhead(df, axs[1], 'wait', True, subtitle_sng)
    
    axs[0].set_ylabel('Wait Time [ns]')
    
    plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=0.5)
    plt.subplots_adjust(top=0.90)
    out_file = 'wait_microbench_hawk_sng.pdf'
    plt.savefig(out_file)
    print(f"Saved figure to {out_file}")
    
    
    ## POST FIGURE
    
    fig, axs = plt.subplots(1, 2, figsize=(16, 4), sharex=True, sharey=True)
    
    subtitle_hawk = f'Post Time on Hawk'
    plot_overhead(hwak_df_compute, axs[0], 'post', False, subtitle_hawk)
    
    subtitle_sng = f'Post Time on SNG'
    plot_overhead(df, axs[1], 'post', True, subtitle_sng)
    
    axs[0].set_ylabel('Post Time [ns]')
    
    plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=0.5)
    plt.subplots_adjust(top=0.90)
    out_file = 'post_microbench_hawk_sng.pdf'
    plt.savefig(out_file)
    print(f"Saved figure to {out_file}")