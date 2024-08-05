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
a,b=map(int,input().split())
MOD=10**9+7
if b==1:
    print(0)
    exit()
s=0
for i in range(1,a+1):
    s+=(b*(b-1)//2)*(i*b+1)
    s%=MOD
print(s)