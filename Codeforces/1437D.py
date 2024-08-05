import sys
from functools import cache
from collections import Counter,defaultdict
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
for t in range(int(input())):
    n=int(input())
    vertices=list(map(int,input().split()))
    ht=1
    remaining=1
    thisLevel=1
    for i in range(2,len(vertices)):
        if vertices[i]<vertices[i-1]:
            remaining-=1
        if remaining==0:
            remaining=thisLevel
            thisLevel=1
            ht+=1
        else:
            thisLevel+=1
    print(ht)