import pandas as pd
import matplotlib.pyplot as plt

def plot_bench_line(df, bench, ax):
    df = df[df['bench'] == bench]
    dfg = df.groupby(['bench', 'conf', 'mode'])
    
    print(df.to_latex())

    # legend_labels = [f'{b} conf={c} mode={m}' for (b,c,m) in dfg.groups]
    legend_labels = [f'conf={c} mode={m}' for (b,c,m) in dfg.groups]

    # dfg.plot(kind='bar', ax=ax, x='nodes', y=['t_default', 't_offload'])
    
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

df = pd.read_csv('hawk-hpgmgfv.csv')

df = df[df['conf'] != 2]
# df = df[df['mode'] == 'multiple']

df['t_default'] = (df['tcore_default'] + df['tresid_default'])
df['t_offload'] = (df['tcore_offload'] + df['tresid_offload'])
df['speedup'] = (df['t_default']) / (df['t_offload'])

benchmarks = df['bench'].unique()

# fig, axs = plt.subplots(len(benchmarks), 1, figsize=(16, 9), sharex=True, sharey=True)
fig, axs = plt.subplots(len(benchmarks), 1, figsize=(16, 9), sharex=False, sharey=False)

for i, bench in enumerate(benchmarks):
    print(i, bench)
    plot_bench_line(df, bench, axs[i])
    
plt.show()

fig.suptitle(f'Hawk: AMD Epyc 7702 Dual-Socket 128 Cores')
    
plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=0.5)
plt.subplots_adjust(top=0.90)
plt.savefig(f'hawk_hpgmgfv.pdf')
