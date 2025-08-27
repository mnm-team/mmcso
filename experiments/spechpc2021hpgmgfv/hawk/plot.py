import pandas as pd
import matplotlib.pyplot as plt

def plot_bench_line(df, bench, ax):
    df = df[df['bench'] == bench]
    dfg = df.groupby(['bench', 'conf', 'mode'])
    
    print(df.to_latex())

    # legend_labels = [f'{b} conf={c} mode={m}' for (b,c,m) in dfg.groups]
    legend_labels = [f'conf={c} mode={m}' for (b,c,m) in dfg.groups]
    for (b,c,m), gp in dfg:
        # gp.plot(x='nodes', y='speedup', ax=ax)
        gp.plot(x='nodes', y='speedup', ax=ax, logx=True)
        # gp.plot(x='nodes', y=['t_default', 't_offload'], ax=ax, logx=True)
        # gp.plot(x='nodes', y=['t_default', 't_offload'], ax=ax, logx=True, logy=True)
        
    ax.legend(labels=legend_labels, # handles=ax.get_legend().legend_handles[0:], 
                                    loc='best',
                                    ncol=1,
                                    labelspacing=0.5,
                                    markerscale=1.5,
                                    frameon=True,
                                    framealpha=0.8,
                                    title=f'Hawk {bench}'
                                    )
    

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
    
    df['speedup_default_multiple'] = df['t_default_funneled'] / df['t_default_multiple']
    df['speedup_offload_multiple'] = df['t_default_funneled'] / df['t_offload_multiple']
    df['speedup_default_funneled'] = df['t_default_funneled'] / df['t_default_funneled']
    df['speedup_offload_funneled'] = df['t_default_funneled'] / df['t_offload_funneled']
    df['speedup_offload'] = df['t_default_multiple'] / df['t_offload_multiple']
    
    dfg = df.groupby(['bench', 'conf'])
    
    print(df.to_string())
    
    ax.grid(alpha=0.3)
    
    position = 0.5
    
    for (b,c), gp in dfg:
        bar = gp.plot(kind='bar', x='nodes', y=[
            # 'speedup_default_funneled', 
            # 'speedup_offload_funneled', 
            'speedup_default_multiple', 
            'speedup_offload_multiple'
            # 'speedup_offload'
            ], 
            ax=ax, 
            grid=True,
            rot=0,
            position=position,
            color={'speedup_default_multiple' : 'darkorange', 'speedup_offload_multiple' : 'darkgreen'}
            )
        # print(bar)
        labels = [f'{label:.2f}' for label in list(df['speedup_offload'])]
        
        ax.bar_label(ax.containers[1], labels=labels, fontsize=7) #, padding=-4.0)
    
    ax.set_xlabel('')
    ax.set_ylabel('Speedup vs. Funneled')
    ax.set_ylabel(bench)
    
    conf1 = '1 MPI proc per Socket'
    conf3 = '1 MPI proc per NUMA domain'
    # ax.set_title(bench)
    
    if bench == '534.hpgmgfv_t':
        # ax.set_title(f'{conf1 if conf == 1 else conf3}\n{bench}')
        ax.set_title(f'{conf1 if conf == 1 else conf3}')
    
    # ax.set_ylim(0.5, 1.2)
    ax.set_ylim(0.0, 1.15)
    
    ax.legend().set_visible(False)
    # ax.hlines(y=1.0, xmin=df['msg_size'].min(), xmax=df['msg_size'].max(), color='darkgrey')

df = pd.read_csv('hawk-hpgmgfv.csv')

# df = df[df['conf'] != 2]
# df = df[df['mode'] == 'multiple']

df['t_default'] = (df['tcore_default'] + df['tresid_default'])
df['t_offload'] = (df['tcore_offload'] + df['tresid_offload'])
df['speedup'] = (df['t_default']) / (df['t_offload'])

# benchmarks = df['bench'].unique()
benchmarks = ['534.hpgmgfv_t', '634.hpgmgfv_s', '734.hpgmgfv_m']

# fig, axs = plt.subplots(len(benchmarks), 1, figsize=(16, 9), sharex=True, sharey=True)
fig, axs = plt.subplots(len(benchmarks), 2, figsize=(9, 9), sharex=False, sharey=True, constrained_layout=False)

for i, bench in enumerate(benchmarks):
    print(i, bench)
    # plot_bench_line(df, bench, axs[i])
    plot_bench_bar(df, bench, 1, axs[i][0])
    plot_bench_bar(df, bench, 3, axs[i][1])

legend_labels = ['Multiple', 'Multiple + Offload']
# legend_labels = ['Funneled', 'Multiple', 'Multiple\n+ Offload']
# legend_labels = ['Funneled', 'Funneled + Offload', 'Multiple', 'Multiple + Offload']
axs[2][0].legend(labels=legend_labels, handles=axs[0][0].get_legend().legend_handles, 
                                loc='center right',
                                ncol=1,
                                labelspacing=0.5,
                                markerscale=1.5,
                                frameon=True,
                                framealpha=0.8,
                                # title=f'Hawk {bench}',
                                title='MPI Mode'
                                # bbox_to_anchor=(0.2, 0.0)
                                )

axs[2][0].set_xlim(axs[1][0].get_xlim())
axs[2][0].set_xticks(axs[1][0].get_xticks())
# axs[2][0].set_xlabel('Nodes')

axs[2][1].set_xlim(axs[1][1].get_xlim())
axs[2][1].set_xticks(axs[1][1].get_xticks())
# axs[2][1].set_xlabel('Nodes')

# fig.supylabel('Speedup vs. Funneled')
fig.supylabel('Performance vs. Funneled')
fig.supxlabel('Nodes', y=0.03)

fig.suptitle(f'Hawk: AMD Epyc 7702 Dual-Socket 128 Cores per Node')
    
plt.tight_layout(pad=1.0, w_pad=0.5, h_pad=1.0)
plt.subplots_adjust(top=0.90)
plt.savefig(f'hawk-hpgmgfv-speedup.pdf')
