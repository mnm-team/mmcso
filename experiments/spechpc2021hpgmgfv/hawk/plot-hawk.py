import pandas as pd
import matplotlib.pyplot as plt

def supylabel2(fig, s, **kwargs):
    defaults = {
        "x": 0.98,
        # "x": 1.00,
        "y": 0.5,
        "horizontalalignment": "center",
        "verticalalignment": "center",
        "rotation": "vertical",
        "rotation_mode": "anchor",
        "size": plt.rcParams["figure.labelsize"],  # matplotlib >= 3.6
        "weight": plt.rcParams["figure.labelweight"],  # matplotlib >= 3.6
    }
    kwargs["s"] = s
    # kwargs = defaults | kwargs  # python >= 3.9
    kwargs = {**defaults, **kwargs}
    fig.text(**kwargs)

def plot_bench_bar(df, bench, conf, ax):
    df = df.loc[df['bench'] == bench]
    df = df.loc[df['conf'] == conf]
    
    if bench == '734.hpgmgfv_m':
        df = df.loc[df['nodes'] >= 64]
    
    df = df[['bench', 'conf', 'mode', 'nodes', 't_default', 't_offload']]
    
    df = pd.merge(df.loc[df['mode'] == 'funneled'], 
                  df.loc[df['mode'] == 'multiple'],
                  on = ['conf', 'nodes', 'bench'],
                  suffixes = ['_funneled', '_multiple']
                  )
    
    # df['speedup_default_multiple'] = df['t_default_funneled'] / df['t_default_multiple']
    # df['speedup_offload_multiple'] = df['t_default_funneled'] / df['t_offload_multiple']
    # df['speedup_default_funneled'] = df['t_default_funneled'] / df['t_default_funneled']
    # df['speedup_offload_funneled'] = df['t_default_funneled'] / df['t_offload_funneled']
    # df['speedup_offload'] = df['t_default_multiple'] / df['t_offload_multiple']
    df['speedup_offload_funneled'] = df['t_default_funneled'] / df['t_offload_multiple']
    df['speedup_offload_multiple'] = df['t_default_multiple'] / df['t_offload_multiple']
    
    dfg = df.groupby(['bench', 'conf'])
    
    print(df.to_string())
    
    ax.grid(alpha=0.3)
    
    position = 0.5
    
    for (b, c), gp in dfg:
        bar = gp.plot(kind='bar', x='nodes', y=[
            't_default_funneled',
            't_default_multiple',
            't_offload_multiple'
            ], 
            ax=ax, 
            grid=True,
            rot=0,
            position=position,
            # logy=True,
            color={'t_default_funneled':'#f4a582', 't_default_multiple':'#92c5de', 't_offload_multiple':'black'}
            )
    
    """
        labels = [f'{label:.2f}' for label in list(df['speedup_offload'])]
        ax.bar_label(ax.containers[1], labels=labels, fontsize=7) #, padding=-4.0)
    """
    
    # add the twin axis
    ax_twin = ax.twinx()
    ax_twin_x_range = range(len(df['nodes']))
    ax_twin.hlines(y=1.0, xmin=-0.5, xmax=7.5, color='darkgrey', linestyle='--')
    ax_twin.plot(ax_twin_x_range, df['speedup_offload_funneled'], color='#ca0020', marker="^", linewidth=1.25)
    ax_twin.plot(ax_twin_x_range, df['speedup_offload_multiple'], color='#0571b0', marker="*", linewidth=1.25)
    ax_twin.set_ylim(0, 2.5)
    
    ax.set_xlabel('')
    # ax.set_ylabel('Speedup vs. Funneled')
    # ax.set_ylabel(bench)
    
    confstr = '1 MPI proc per Socket' if conf == 1 else '1 MPI proc per NUMA domain'
    ax.set_ylabel(confstr)
    
    if conf == 1:
        ax.set_title(f'{bench[4:]}')
        ax.set_xticklabels([])
        
    ax.legend().set_visible(False)
    if bench == '734.hpgmgfv_m':
        # ax_twin.set_ylabel('Speedup')
        if conf == 1:
            legend_labels = ['Funneled', 'Multiple', 'Offload']
            ax.legend(labels=legend_labels, handles=ax.get_legend().legend_handles, 
                                    loc='upper right',
                                    ncol=1,
                                    labelspacing=0.5,
                                    markerscale=1.5,
                                    frameon=True,
                                    framealpha=0.8,
                                    title='Communication Mode'
                                    # bbox_to_anchor=(0.2, 0.0)
                                    )
        else:
            legend_labels_speedup = ['Offload vs. Funneled', 'Offload vs. Multiple']
            ax_twin.legend(labels=legend_labels_speedup + ['dummy'], title='Speedup')
            ax_twin.legend(labels=legend_labels_speedup, handles=ax_twin.get_legend().legend_handles[1:], title='Speedup')
    else:
        ax_twin.get_yaxis().set_visible(False)

df = pd.read_csv('hawk-hpgmgfv.csv')

df['t_default'] = (df['tcore_default'] + df['tresid_default'])
df['t_offload'] = (df['tcore_offload'] + df['tresid_offload'])
df['speedup'] = (df['t_default']) / (df['t_offload'])

benchmarks = ['534.hpgmgfv_t', '634.hpgmgfv_s', '734.hpgmgfv_m']
fig, axs = plt.subplots(2, len(benchmarks), figsize=(15, 7), sharex=False, sharey=True, constrained_layout=False)

for i, bench in enumerate(benchmarks):
    print(i, bench)
    plot_bench_bar(df, bench, 1, axs[0][i])
    plot_bench_bar(df, bench, 3, axs[1][i])

axs[0][2].set_xlim(axs[1][0].get_xlim())
axs[0][2].set_xticks(axs[1][0].get_xticks())
# axs[0][2].set_xlabel('Nodes')

axs[1][2].set_xlim(axs[1][1].get_xlim())
axs[1][2].set_xticks(axs[1][1].get_xticks())
# axs[1][2].set_xlabel('Nodes')

# fig.supylabel('Speedup vs. Funneled')
fig.supylabel('Execution Time (s)', x=0.01)
supylabel2(fig, 'Speedup', x=0.99)

fig.supxlabel('Nodes', y=0.02)

# fig.suptitle(f'Hawk: AMD Epyc 7702 | 128 Cores per Node')
    
plt.tight_layout(pad=1.0, w_pad=0.5, h_pad=1.0)
# plt.subplots_adjust(top=0.90)
plt.subplots_adjust(right=0.95)
plt.savefig(f'hawk-hpgmgfv-speedup.pdf')
