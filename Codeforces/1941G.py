from collections import defaultdict,deque
import sys
def input():
    return sys.stdin.readline().rstrip("\r\n")
t=int(input())
for _ in range(t):
    n,m=map(int,input().split())
    edges=[list(map(int,input().split())) for _ in range(m)]
    src,dest=map(int,input().split())
    idx=n+1
    colors=defaultdict(int)
    for u,v,c in edges:
        if c not in colors:
            colors[c]=idx
            idx+=1
    mp=defaultdict(list)
    for u,v,c in edges:
        col=colors[c]
        mp[u].append(col)
        mp[col].append(u)
        mp[v].append(col)
        mp[col].append(v)
    levels=[-1]*idx
    levels[src]=0
    q=deque([src])
    while q:
        if levels[dest]!=-1:
            print(levels[dest]//2)
            break
        node=q.popleft()
        for neighbor in mp[node]:
            if levels[neighbor]==-1:
                levels[neighbor]=levels[node]+1
                q.append(neighbor)