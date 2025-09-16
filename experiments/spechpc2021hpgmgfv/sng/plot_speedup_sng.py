import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def plot_bench_bar(df, bench, conf, ax, num_plots, plot_idx):

    df = df.loc[df['bench'] == bench]
    df = df.loc[df['conf'] == conf]
    
    if bench == 'hpgmgfv_t':
        df = df.loc[df['nodes'] <= 128]
    elif bench == 'hpgmgfv_s':
        df = df.loc[df['nodes'] >= 4]
    elif bench == 'hpgmgfv_m':
        df = df.loc[df['nodes'] >= 64]
    
    df = df[['bench', 'conf', 'nodes', 't_funneled', 't_multiple', 't_offload', 
             'speedup_offload_vs_funneled', 'speedup_offload_vs_multiple']]
    
    # df = pd.merge(df.loc[df['mode'] == 'multiple'],
    #               on = ['conf', 'nodes', 'bench'],
    #               suffixes = ['_funneled', '_multiple']
    #               )
    
    dfg = df.groupby(['bench', 'conf'])
    
    # print(df.to_string())
    
    ax.grid(alpha=0.3)
    
    position = 0.5
    
    # add the twin axis
    ax_twin = ax.twinx()
    ax_twin_x_range = np.arange(len(df['nodes']))
    ax_twin.hlines(y=1.0, xmin=-0.5, xmax=7.5, color='darkgrey', linestyle='--')
    # print("Check ax_twin_y_range: ", ax_twin_x_range)

    for (b, c), gp in dfg:
        bar = gp.plot(kind='bar', x='nodes', y=[
            # 'speedup_default_funneled', 
            # 'speedup_offload_funneled', 
            't_funneled',
            't_multiple',
            't_offload'
            # 'speedup_offload'
            ], 
            ax=ax, 
            grid=True,
            rot=0,
            position=position,
            # logy=True,
            color={'t_funneled':'#f4a582', 't_multiple':'#92c5de', 't_offload':'black'}
            )
        # gp.plot(x='nodes', y='speedup_offload', ax=ax_twin)
        # print(bar)
        # labels = [f'{label:.2f}' for label in list(df['speedup_offload'])]
        
        # ax.bar_label(ax.containers[1], labels=labels, fontsize=7) #, padding=-4.0)
    
    ax_twin.plot(ax_twin_x_range, df['speedup_offload_vs_funneled'], color='#ca0020', marker="^", linewidth=1.25)
    ax_twin.plot(ax_twin_x_range, df['speedup_offload_vs_multiple'], color='#0571b0', marker="*", linewidth=1.25)
    if plot_idx == num_benches - 1:
        ax_twin.set_ylabel('Speedup')
    ax_twin.set_ylim(0, 2.5)
    
    ax.set_xlabel('')
    ax.set_ylabel('Execution Time (s)')
    # ax.set_ylabel(bench)
    ax.set_title(bench)
    
    conf1 = '1 MPI proc per Socket'
    conf3 = '1 MPI proc per NUMA domain'
    # ax.set_title(bench)
    
    # if bench == 'hpgmgfv_t':
        # ax.set_title(f'{conf1 if conf == 1 else conf3}\n{bench}')
        # ax.set_title(f'{conf1 if conf == 1 else conf3}')

    # ax.set_ylim(0.5, 1.2)
    # ax.set_ylim(0, 900)
    
    ax.legend().set_visible(False)
    
    return ax_twin

# ------------------------------------------------
# Plot the figures
# ------------------------------------------------

df = pd.read_csv('sng_spechpc_hpgmgfv_updated.csv')

# df = df[df['conf'] != 2]
# df = df[df['mode'] == 'multiple']

df['t_funneled'] = (df['tcore_funneled'] + df['tresid_funneled'])
df['t_multiple'] = (df['tcore_multiple'] + df['tresid_multiple'])
df['t_offload'] = (df['tcore_offload'] + df['tresid_offload'])
df['speedup_offload_vs_funneled'] = (df['t_funneled']) / (df['t_offload'])
df['speedup_offload_vs_multiple'] = (df['t_multiple']) / (df['t_offload'])

# benchmarks = df['bench'].unique()
# benchmarks = ['534.hpgmgfv_t', '634.hpgmgfv_s', '734.hpgmgfv_m']
benchmarks = ['hpgmgfv_t', 'hpgmgfv_s', 'hpgmgfv_m']

num_benches = len(benchmarks)
fig, axs = plt.subplots(1, num_benches, figsize=(15, 5), sharex=False, sharey=True, constrained_layout=False)

axs_twin = []

for i, bench in enumerate(benchmarks):
    # print(i, bench)
    # plot_bench_line(df, bench, axs[i])
    twin = plot_bench_bar(df, bench, 1, axs[i], num_benches, i)
    axs_twin = axs_twin + [twin]
    # plot_bench_bar(df, bench, 3, axs[i][1])
    
# remove y-axis except in right subplot
for ax in axs_twin[:-1]:
    ax.get_yaxis().set_visible(False)

legend_labels = ['Funneled', 'Multiple', 'Offload']
legend_labels_speedup = ['Offload vs. Funneled', 'Offload vs. Multiple']
# legend_labels = ['Funneled', 'Multiple', 'Multiple\n+ Offload']
# legend_labels = ['Funneled', 'Funneled + Offload', 'Multiple', 'Multiple + Offload']

axs[2].legend(labels=legend_labels, handles=axs[0].get_legend().legend_handles, 
                                loc='lower right',
                                ncol=1,
                                labelspacing=0.5,
                                markerscale=1.5,
                                frameon=True,
                                framealpha=0.8,
                                # title=f'Hawk {bench}',
                                title='Communication Mode'
                                # bbox_to_anchor=(0.2, 0.0)
                                )

axs_twin[2].legend(labels=legend_labels_speedup + ['dummy'], title='Speedup')
axs_twin[2].legend(labels=legend_labels_speedup, handles=axs_twin[2].get_legend().legend_handles[1:], title='Speedup')

axs[2].set_xlim(axs[1].get_xlim())
axs[2].set_xticks(axs[1].get_xticks())
# axs[2][0].set_xlabel('Nodes')

axs[2].set_xlim(axs[1].get_xlim())
axs[2].set_xticks(axs[1].get_xticks())
# axs[2][1].set_xlabel('Nodes')

# fig.supylabel('Speedup vs. Funneled')
# fig.supylabel('Execution Time (s)')
fig.supxlabel('Nodes', y=0.03)

fig.suptitle(f'SNG: Intel Skylake Xeon Platinum 8174 | 48 Cores per Node')
    
plt.tight_layout(pad=1.0, w_pad=0.5, h_pad=1.0)
# plt.subplots_adjust(top=0.90)
plt.savefig(f'sng-hpgmgfv-speedup.pdf')
