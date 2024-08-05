from collections import Counter
from math import factorial,comb
n,k=map(int,input().split())
der={4:9,3:2,2:1,1:0,0:1}
res=0
for i in range(k+1):
    res+=comb(n,i)*der[i]
print(res)