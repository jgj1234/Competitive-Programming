from collections import Counter,defaultdict,deque
from typing import List
from math import factorial,comb,log2,floor
from functools import cache
for case in range(1):
    n,m,h=map(int,input().split())
    nums=list(map(int,input().split()))
    h-=1
    otherSum=sum(nums)-nums[h]
    if otherSum+nums[h]<n:
        print(-1)
        continue
    elif otherSum<n-1:
        print(1)
        continue
    denominator = comb(otherSum+nums[h]-1,n-1)
    numerator =denominator - comb(otherSum,n-1)
    print(numerator/denominator)