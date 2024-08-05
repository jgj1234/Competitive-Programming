import sys
from functools import cache
from collections import Counter,defaultdict
from types import GeneratorType
def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to
    return wrappedfunc
def input():
    return sys.stdin.readline().rstrip('\r\n')
def solve():
    n,k=map(int,input().split())
    nodeMap=defaultdict(list)
    
    for i in range(n-1):
        u,v=map(int,input().split())
        nodeMap[u-1].append(v-1)
        nodeMap[v-1].append(u-1)
    def check(x):
        res=0
        @bootstrap
        def dfs(node,parent):
            nonlocal res
            sz=1
            for neighbor in nodeMap[node]:
                if neighbor!=parent:
                    sz+=yield dfs(neighbor,node)
            if sz>=x and node!=parent:
                res+=1
                sz=0
            yield sz
        t=dfs(0,0)
        return res>k or (res==k and t>=x)
    low=1   
    high=n
    while low+1<high:
        mid=(low+high)//2
        if check(mid):
            low=mid
        else:
            high=mid
    print(low)
t=int(input())
for _ in range(t):
    solve()