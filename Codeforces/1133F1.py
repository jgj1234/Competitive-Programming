import sys
from functools import cache
from collections import Counter,defaultdict,deque
from itertools import combinations
from types import GeneratorType
from typing import List
import math
import heapq
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
n,m=map(int,input().split())
nodeMap=defaultdict(list)
for _ in range(m):
    u,v=map(int,input().split())
    nodeMap[u].append(v)
    nodeMap[v].append(u)
maxNode=-1
for key in nodeMap:
    if maxNode==-1 or len(nodeMap[key])>len(nodeMap[maxNode]):
        maxNode=key
q=deque([maxNode])
visited={maxNode}
while q:
    node=q.popleft()
    for neighbor in nodeMap[node]:
        if neighbor not in visited:
            visited.add(neighbor)
            print(node,neighbor)
            q.append(neighbor)