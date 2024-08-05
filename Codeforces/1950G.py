import sys
from functools import cache
from collections import Counter,defaultdict
from types import GeneratorType
from typing import List
import math
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
t=int(input())

for _ in range(t):
    n=int(input())
    songs=[]
    g=w=0
    gs=defaultdict(int)
    ws=defaultdict(int)
    for i in range(n):
        genre,writer=input().split()
        r=[]
        if genre not in gs:
            gs[genre]=g
            r.append(g)
            g+=1
        else:
            r.append(gs[genre])
        if writer not in ws:
            ws[writer]=w
            r.append(w)
            w+=1
        else:
            r.append(ws[writer])
        songs.append(r)
    @cache
    def findMinimum(bitmask,prev,left):
        if left==0:
            return 0
        count=left
        for i in range(len(songs)):
            if bitmask&(1<<i)==0 and (left==n or songs[i][0]==songs[prev][0] or songs[i][1]==songs[prev][1]):
                count=min(count,findMinimum(bitmask|(1<<i),i,left-1))
        return count
    print(findMinimum(0,-1,n))