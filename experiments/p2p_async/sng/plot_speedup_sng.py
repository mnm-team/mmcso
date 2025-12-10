import os,sys
import matplotlib.pyplot as plt
import pandas as pd

os.chdir(sys.path[0])

linestyles = { True: ':', False: '-.' }
colors = ['darkorange', 'darkgreen', 'mediumvioletred', 'darkblue', 'grey', 'cyan']

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
        dfs = dfs + [df]
    df_concat = pd.concat(dfs, ignore_index=True)
    # print(df_concat)
    return df_concat

def plot_speedup(df, ax, title, is_mem):

    ax.hlines(y=1.0, xmin=df['msg_size'].min(), xmax=df['msg_size'].max(), color='darkgrey')
    
    dfs = []
    modes = [mode for mode in df['mode'].unique() if mode != 'native' and 'split' not in mode]
    df_baseline = df.loc[df['mode'] == 'native'].reset_index()
    for mode in modes:
        dfm = df.loc[df['mode'] == mode].reset_index()
        dfm['speedup'] = df_baseline['comm_time'] / dfm['comm_time']
        dfs.append(dfm)
        
    df = pd.concat(dfs, ignore_index=True)
    
    print(df.to_string())
    
    if is_mem:
        df = df[(df['work'] == 500) | (df['work'] == 5000) | (df['work'] == 50000) | (df['work'] == 500000)]
    else:
        df = df[(df['work'] == 100) | (df['work'] == 1000) | (df['work'] == 10000) | (df['work'] == 100000)]
    
    df = df[(df['mode'] == 'offload') | ((df['mode'] == 'async') & ((df['work'] == 500) | (df['work'] == 100) | (df['work'] == 500000) | (df['work'] == 100000)))]
    
    # print(df.to_string())
    
    # sort df so async is plotted last
    df = df.sort_values(['mode', 'msg_size'], ascending=False, ignore_index=True)
    dfg = df.groupby(['mode', 'work'], sort=False)
    
    for i, ((w), gp) in enumerate(dfg):
        # line = gp.plot(ax=ax, x='msg_size', y='speedup', logx=True, logy=False, color=colors[i], linestyle='-.' if is_mem else ':', 
        #                marker='^' if is_mem else 'o', markerfacecolor='none', markersize=8)
                       #, yerr='std', elinewidth=0.1, capsize=3, capthick=0.1)
                       
        print(w)
        # print(gp)
        is_async = (w[0] == 'async')
        
        label = f'{w[1]//100} kbyte' if is_mem else f'{w[1]} ns'
        if is_async:
            label = label + ' (async)'
                       
        line = gp.plot(ax=ax, x='msg_size', y='speedup', logx=True, logy=False, 
                       linestyle='dashed' if is_async else '-.' if is_mem else ':', 
                    #    marker='x' if '^' if is_mem else 'o', 
                       marker='x' if is_async else '^' if is_mem else 'o', 
                    #    linewidth = 0.8,
                       markerfacecolor='none', 
                    #    markersize=5, 
                       markersize=8, 
                       color=colors[i],
                       label=label
                       )
    
    # legend_labels = []
    
    """
    if is_mem:
        # legend_labels = [f"{10*work//1000} kbytes" for work in dfg.groups]
        # ax.set_ylabel('Speedup (memcpy)')
        ax.set_title('memcpy')
    else:
        # ax.set_title(title)
        # legend_labels = [f"{work} ns" for work in dfg.groups]
        # ax.set_ylabel('Speedup')
        ax.set_title('sleep')
    """
     
    ax.set_ylabel('Speedup')
        
    ax.legend(#handles=ax.get_legend().legend_handles[0:], labels=legend_labels,
                                 loc='best',
                                 ncol=1,
                                 labelspacing=0.5,
                                 markerscale=1.5,
                                 frameon=True,
                                 framealpha=0.8,
                                 title=f"Work ({'memcpy' if is_mem else 'sleep'})"
                                 )
    
def plot(axs, df, mode, is_mem):
    
    conf1 = ('2-4', '1 MPI proc per Socket, 63 threads per MPI proc')
    conf2 = ('2-8', '2 MPI proc per Socket, 31 threads per MPI proc')
    conf3 = ('2-16', '1 MPI proc per NUMA domain, 15 threads per MPI proc')
    conf4 = ('2-4', '1 MPI proc per Socket, 23 threads per MPI proc')
    
    configs = [conf4]
    
    # df = df.loc[(df['mode'] == 'native') | (df['mode'] == mode)]
    
    # ymax = 3.5
    # ymax = 17.5
    # ytickmax = math.ceil(ymax)
    
    # data frames for non-memory-intensive work
    for i, (conf, title) in enumerate(configs):
        # df = df[(df['work'] == 100) | (df['work'] == 1000) | (df['work'] == 10000) | (df['work'] == 100000)]
        df = df.groupby(['nthreads', 'msg_size', 'mode', 'work']).mean().drop(['rank', 'thread'], axis=1).reset_index()
        plot_speedup(df, axs, title, is_mem)
    
    axs.grid(alpha=0.3)
    axs.set_xlim(2, 1.0e9)
    axs.set_xlabel('Message Size [bytes]')
    # axs.set_ylabel('speedup')
    # axs.set_yticks(range(ytickmax))
    # axs.set_ylim(0.5, ymax)
    # axs.legend().set_visible(False)
        
    # axs[1].legend().set_visible(False)

if __name__ == '__main__':

    fig, axs = plt.subplots(1, 2, figsize=(16, 4), sharex=True, sharey=True)
    
    result_dir = './result'
    
    csv_files = [f for f in os.listdir(result_dir) if os.path.isfile(f'{result_dir}/{f}') and f.endswith('.csv')]
    
    csv_files_compute = [f'{result_dir}/{f}' for f in csv_files if not f.endswith('-mem.csv')]
    csv_files_mem = [f'{result_dir}/{f}' for f in csv_files if f.endswith('-mem.csv')]
    
    print(csv_files_compute, csv_files_mem)
    
    df_compute = make_dataframe(csv_files_compute)
    df_mem = make_dataframe(csv_files_mem)
    
    plot(axs[0], df_compute, 'offload', False)
    plot(axs[1], df_mem, 'offload', True)
    
    # plot(axs[0][0], df_compute, 'offload', False)
    # plot(axs[1][0], df_mem, 'offload', True)
    # plot(axs[0][1], df_compute, 'async', False)
    # plot(axs[1][1], df_mem, 'async', True)
    
    # fig.suptitle(f'SNG: Intel Xeon(R) Gold 6148 48 Cores \n(2 Nodes, 1 MPI proc per Socket, 23 threads per MPI proc)')
    fig.suptitle(f'SNG, 2 Nodes, 1 MPI proc per Socket, 23 threads per MPI proc')
    # fig.suptitle(f'1 MPI proc per Socket, 23 threads per MPI proc')
    
    plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=0.5)
    plt.subplots_adjust(top=0.90)
    plt.savefig(f'./speedup_microbench_sng.pdf')
    print("Saved figure to ./speedup_microbench_sng.pdf")
    
    # plt.show()