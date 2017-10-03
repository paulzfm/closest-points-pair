#!/usr/bin/python

# running

import os

FROM = 10000
TO = 100000
STEP = 10000
BOUND = 50000
MAX_X = 10000
MAX_Y = 10000

ns = range(FROM, TO, STEP)
ts_bf = []
ts_opt = []

for n in ns:
    arg = ''
    if n <= BOUND:
        arg = 'a'
    else:
        arg = 'o'
        ts_bf.append(-1)
    output = os.popen('../core/closest -r %d %f %f %s' % (n, MAX_X, MAX_Y, arg))
    lines = output.read().split('\n')
    for line in lines:
        if line.startswith('Brute-force: time (ms): '):
            ts_bf.append(float(line[24:]))
        elif line.startswith('Optimal: time (ms): '):
            ts_opt.append(float(line[20:]))

# table
with open('table.tex', 'w+') as f:
    f.write("""\\begin{tabular}{rll}
\\toprule
\\multirow{2}{*}{Number of points} & \\multicolumn{3}{c}{Run time (ms)} \\\\
& Brute-force & Optimal \\\\
\\midrule
""")
    for X in zip(ns, ts_bf, ts_opt):
        f.write('%d & %f & %f \\\\\n' % X)
    f.write("""\\bottomrule
\\end{tabular}
    """)
    f.close()
    print('table.tex saved')

# plot
import numpy as np
import matplotlib.pyplot as plt

plt.xlabel('number of points')
plt.ylabel('time elapsed (ms)')
plt.axis([10000, 100000, 0, 14000])
bf, = plt.plot(ns, ts_bf, '+b')
opt, = plt.plot(ns, ts_opt, 'dg')
plt.legend([bf, opt], ['Brute-force', 'Optimal'])
fig = plt.gcf() # 'get current figure'
fig.savefig('cpp.eps', format='eps', dpi=1000)
print('cpp.eps saved')
plt.close('all')

# large scale
ns = range(100000, 1100000, 100000)
ts = []
for n in ns:
    output = os.popen('../core/closest -r %d %f %f' % (n, MAX_X, MAX_Y))
    lines = output.read().split('\n')
    for line in lines:
        if line.startswith('Optimal: time (ms): '):
            ts.append(float(line[20:]))

print ts

plt.xlabel('number of points (k)')
plt.ylabel('time elapsed (ms)')
plt.plot(map(lambda x: x/1000, ns), ts, 'dg')
fig = plt.gcf() # 'get current figure'
fig.savefig('opt.eps', format='eps', dpi=1000)
print('opt.eps saved')
plt.close('all')
