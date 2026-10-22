#!/usr/bin/env python3
"""独立暴力基线对拍：固定随机种子；错误时打印可复现输入。"""
import argparse
import itertools as it
import json
import random
from collections import deque
from pathlib import Path
from lab import ROOT, BY_ID, compile_source, execute

parser = argparse.ArgumentParser()
parser.add_argument('--rounds', type=int, default=40)
parser.add_argument('--seed', type=int, default=20261021)
args = parser.parse_args()
if args.rounds < 1: parser.error('--rounds 必须为正数')
rng = random.Random(args.seed)
binaries = {}
counts = {}


def expect(id, data, answer, timeout=3):
    if id not in binaries: binaries[id] = compile_source(ROOT/BY_ID[id]['path'])
    wanted = ' '.join(map(str, answer)) if isinstance(answer, list) else str(answer)
    actual = execute(binaries[id], data, timeout)
    if actual.split() != wanted.split():
        raise AssertionError(f'{id}\ninput={data!r}\nexpected={wanted!r}\nactual={actual!r}')
    counts[id] = counts.get(id, 0)+1


def line(values): return ' '.join(map(str, values))+'\n'


def components(n, edges):
    g = [[] for _ in range(n)]
    for u,v in edges: g[u].append(v);g[v].append(u)
    groups=[];seen=set()
    for root in range(n):
        if root in seen: continue
        seen.add(root); todo=[root]; group=[]
        while todo:
            u=todo.pop();group.append(u)
            for v in g[u]:
                if v not in seen:seen.add(v);todo.append(v)
        groups.append(group)
    return groups


for _ in range(args.rounds):
    n=rng.randint(1,8);a=[rng.randint(-8,8) for _ in range(n)]
    expect('sum64',line([n])+line(a),sum(a))
    bound=rng.randint(1,500)
    expect('digit_filter',line([bound]),sum('2' in str(x) for x in range(1,bound+1)))
    expect('real_good_numbers',line([bound]),sum(all(int(c)%2==(i+1)%2 for i,c in enumerate(str(x)[::-1])) for x in range(1,bound+1)))
    expect('digit_dp',line([bound]),sum('4' not in str(x) for x in range(bound+1)))
    records=[(rng.choice(['ann','bob','cat']),rng.randint(0,5)) for _ in range(n)]
    text=line([n])+''.join(f'{name} {score}\n' for name,score in records)
    expected=[z for rec in sorted(records,key=lambda p:(-p[1],p[0])) for z in rec]
    expect('ranking',text,expected)
    words=[p[0] for p in records]
    expect('frequency',line([n])+line(words),[z for w in sorted(set(words)) for z in (w,words.count(w))])
    s=''.join(rng.choice('()[]{}') for _ in range(rng.randint(0,20)))
    reduced=s
    while True:
        newer=reduced.replace('()','').replace('[]','').replace('{}','')
        if newer==reduced:break
        reduced=newer
    expect('brackets',s+'\n','YES' if not reduced else 'NO')
    queries=[sorted([rng.randint(1,n),rng.randint(1,n)]) for _ in range(6)]
    expect('prefix',line([n,len(queries)])+line(a)+''.join(line(q) for q in queries),[sum(a[l-1:r]) for l,r in queries])
    ops=[(l,r,rng.randint(-5,5)) for l,r in queries];baseline=[0]*n
    for l,r,d in ops:
        for i in range(l-1,r):baseline[i]+=d
    expect('difference',line([n,len(ops)])+''.join(line(o) for o in ops),baseline)
    nonneg=[abs(x) for x in a];limit=rng.randint(0,20)
    expect('window',line([n,limit])+line(nonneg),sum(sum(nonneg[l:r+1])<=limit for l in range(n) for r in range(l,n)))
    positive=[x+1 for x in nonneg];days=rng.randint(1,n)
    # 枚举全部切分点；不调用二分版的贪心判定器。
    cap=sum(positive)
    for mask in range(1<<(n-1)):
        cuts=[0]+[i+1 for i in range(n-1) if mask>>i&1]+[n]
        if len(cuts)-1<=days:cap=min(cap,max(sum(positive[l:r]) for l,r in zip(cuts,cuts[1:])))
    expect('capacity',line([n,days])+line(positive),cap)
    intervals=[]
    for i in range(n):
        l=rng.randint(0,9);intervals.append((l,l+rng.randint(1,5)))
    best=0
    for mask in range(1<<n):
        selected=sorted(intervals[i] for i in range(n) if mask>>i&1)
        if all(x[1]<=y[0] for x,y in zip(selected,selected[1:])):best=max(best,len(selected))
    expect('intervals',line([n])+''.join(line(p) for p in intervals),best)
    target=rng.randint(0,20)
    subset_sums=[sum(nonneg[i] for i in range(n) if mask>>i&1) for mask in range(1<<n)]
    expect('subsets',line([n,target])+line(nonneg),subset_sums.count(target))
    budget=rng.randint(0,20);values=[rng.randint(0,20) for _ in range(n)]
    optimum=max(sum(values[i] for i in range(n) if mask>>i&1) for mask in range(1<<n)
                if sum(positive[i] for i in range(n) if mask>>i&1)<=budget)
    expect('knapsack',line([n,budget])+''.join(line([c,v]) for c,v in zip(positive,values)),optimum)
    lengths=[]
    for mask in range(1<<n):
        seq=[a[i] for i in range(n) if mask>>i&1]
        if all(x<y for x,y in zip(seq,seq[1:])):lengths.append(len(seq))
    expect('lis',line([n])+line(a),max(lengths))
    p=rng.randint(1,100);qs=list(range(p+1))
    expect('sieve',line([p,len(qs)])+line(qs),['YES' if x>=2 and all(x%d for d in range(2,x)) else 'NO' for x in qs])
    base=rng.randint(0,10**18);power=rng.randint(0,10000);mod=rng.randint(1,10**9)
    expect('powmod',line([base,power,mod]),pow(base,power,mod))
    mutable=a[:];commands=[];answers=[]
    for l,r in queries:
        if rng.randrange(2):
            delta=rng.randint(-9,9);commands.append((1,l,delta));mutable[l-1]+=delta
        else:commands.append((2,l,r));answers.append(sum(mutable[l-1:r]))
    expect('fenwick',line([n,len(commands)])+line(a)+''.join(line(c) for c in commands),answers)
    k=rng.randint(1,n)
    expect('windowmax',line([n,k])+line(a),[max(a[i:i+k]) for i in range(n-k+1)])
    text=''.join(rng.choice('abc') for _ in range(30));pattern=''.join(rng.choice('abc') for _ in range(rng.randint(1,6)))
    expect('kmp',text+'\n'+pattern+'\n',sum(text[i:i+len(pattern)]==pattern for i in range(len(text))))
    # 直接枚举不同合并操作顺序，与区间 DP 的转移表达式独立。
    from functools import lru_cache
    @lru_cache(None)
    def merge(values):
        if len(values)==1:return 0
        return min(values[i]+values[i+1]+merge(values[:i]+(values[i]+values[i+1],)+values[i+2:]) for i in range(len(values)-1))
    small=tuple(nonneg[:6]);expect('merge_cost',line([len(small)])+line(small),merge(small))
    tree=[(i,rng.randrange(i)) for i in range(1,n)]
    best=max(sum(values[i] for i in range(n) if mask>>i&1) for mask in range(1<<n)
             if all(not(mask>>u&1 and mask>>v&1) for u,v in tree))
    expect('tree_party',line([n])+line(values)+''.join(line([u+1,v+1]) for u,v in tree),best)
    size=min(n,7);cost=[[0 if i==j else rng.randint(0,15) for j in range(size)] for i in range(size)]
    best=min(sum(cost[u][v] for u,v in zip((0,)+p,p+(0,))) for p in it.permutations(range(1,size)))
    expect('tsp',line([size])+''.join(line(row) for row in cost),best)
    actual_v=rng.randint(1,10);aa=[rng.randint(actual_v,80) for i in range(4)]
    rec=[(x,x//actual_v) for x in aa];allowed=[v for v in range(1,81) if all(x//v==b for x,b in rec)]
    expect('real_smelting',line([len(rec)])+''.join(line(p) for p in rec),[min(allowed),max(allowed)])
    weights=positive[:7];reachable={abs(sum(w*s for w,s in zip(weights,signs))) for signs in it.product([-1,0,1],repeat=len(weights))}
    expect('real_weights',line([len(weights)])+line(weights),len(reachable-{0}))
    planes=[(rng.randint(0,8),rng.randint(0,5),rng.randint(0,4)) for i in range(min(n,6))]
    possible=False
    for perm in it.permutations(planes):
        now=0;ok=True
        for arrive,wait,duration in perm:
            now=max(now,arrive)
            if now>arrive+wait:ok=False;break
            now+=duration
        if ok:possible=True;break
    expect('real_landing','1\n'+line([len(planes)])+''.join(line(p) for p in planes),'YES' if possible else 'NO')
    h=rng.randint(1,4);w=rng.randint(1,4);matrix=[[rng.randint(0,4) for _ in range(w)] for _ in range(h)];K=rng.randint(1,15)
    answer=sum(sum(matrix[i][j] for i in range(top,bottom+1) for j in range(left,right+1))<=K
               for top in range(h) for bottom in range(top,h) for left in range(w) for right in range(left,w))
    expect('real_submatrix',line([h,w,K])+''.join(line(row) for row in matrix),answer)
    # 迷宫用反复松弛的慢基线，而不是再次实现 BFS。
    grid=[''.join(rng.choice('...#') for _ in range(w)) for _ in range(h)]
    dist=[[10000]*w for _ in range(h)]
    if grid[0][0]!='#':dist[0][0]=0
    for turn in range(h*w):
        for i in range(h):
            for j in range(w):
                if grid[i][j]=='#':continue
                for x,y in ((i-1,j),(i+1,j),(i,j-1),(i,j+1)):
                    if 0<=x<h and 0<=y<w and grid[x][y]!='#':dist[x][y]=min(dist[x][y],dist[i][j]+1)
    expect('maze',line([h,w])+'\n'.join(grid)+'\n',dist[-1][-1] if dist[-1][-1]<10000 else -1)
    size=rng.randint(1,6);edges=[(rng.randrange(size),rng.randrange(size)) for i in range(rng.randint(1,8))]
    edge_input=''.join(line([u+1,v+1]) for u,v in edges)
    original=len(components(size,edges));bridge_count=0;weight=[rng.randint(0,9) for i in range(size)];diffs=[]
    for i in range(len(edges)):
        groups=components(size,edges[:i]+edges[i+1:])
        bridge_count+=len(groups)>original
        if len(groups)==2:diffs.append(abs(sum(weight[v] for v in groups[0])-sum(weight[v] for v in groups[1])))
    expect('bridges',line([size,len(edges)])+edge_input,bridge_count)
    expect('real_delete_edge',line([size,len(edges)])+line(weight)+edge_input,min(diffs) if diffs else -1)
    removed=rng.sample(range(len(edges)),rng.randint(0,len(edges)));gone=set();answers=[]
    for e in removed:
        gone.add(e);answers.append(len(components(size,[p for i,p in enumerate(edges) if i not in gone])))
    expect('offline_connectivity',line([size,len(edges),len(removed)])+edge_input+line([i+1 for i in removed]),answers)
    # 连通性查询基线每次重建图并遍历。
    added=[];commands=[];answers=[]
    for u,v in edges:
        if rng.randrange(2):commands.append((1,u+1,v+1));added.append((u,v))
        else:
            commands.append((2,u+1,v+1))
            answers.append('YES' if any(u in c and v in c for c in components(size,added)) else 'NO')
    expect('dsu',line([size,len(commands)])+''.join(line(c) for c in commands),answers)
    weighted=[(u,v,rng.randint(0,20)) for u,v in edges];source=rng.randrange(size)
    d=[10**12]*size;d[source]=0
    for turn in range(size):
        for u,v,c in weighted:
            if d[u]<10**12:d[v]=min(d[v],d[u]+c)
    expect('dijkstra',line([size,len(edges),source+1])+''.join(line([u+1,v+1,c]) for u,v,c in weighted),[x if x<10**12 else -1 for x in d])
    spanning=[]
    for chosen in it.combinations(weighted,size-1):
        if len(components(size,[(u,v) for u,v,c in chosen]))==1:spanning.append(sum(c for u,v,c in chosen))
    expect('kruskal',line([size,len(edges)])+''.join(line([u+1,v+1,c]) for u,v,c in weighted),min(spanning) if spanning else -1)

# 大规模性质检查：64 位计数、深链栈安全、范围上界。
n=200000
expect('sum64',line([n])+line([10**9]*n),n*10**9)
expect('window',line([n,0])+line([0]*n),n*(n+1)//2)
chain=''.join(f'{i} {i+1}\n' for i in range(1,n))
expect('bridges',line([n,n-1])+chain,n-1,8)
expect('tree_party',line([n])+line([1]*n)+chain,(n+1)//2,8)
expect('real_delete_edge',line([n,n-1])+line([10**9]*n)+chain,0,8)
expect('digit_dp','1000000000000000000\n',9**18+1)
expect('real_submatrix','500 500 1\n'+(' '.join(['0']*500)+'\n')*500,(500*501//2)**2,8)
assert set(counts)==set(BY_ID), f'缺少对拍：{set(BY_ID)-set(counts)}'
report={'seed':args.seed,'rounds':args.rounds,'checks':sum(counts.values()),'per_task':counts}
(ROOT/'build').mkdir(exist_ok=True)
(ROOT/'build/verification.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(f'PASS: {len(counts)} programs, {sum(counts.values())} differential/property checks; seed={args.seed}')
