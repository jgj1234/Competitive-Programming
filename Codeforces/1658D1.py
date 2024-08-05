import sys
import math
def input():
    return sys.stdin.readline().rstrip('\r\n')
t=int(input())
for _ in range(t):
    l,r=map(int,input().split())
    nums=list(map(int,input().split()))
    res=0
    for bit in range(19):
        length=2**(bit+1)
        ones=(r//length)*(length//2)+max(0,(r+1)%length-length//2)
        oc=0
        for i in range(len(nums)):
            if nums[i]&(1<<bit):
                oc+=1
        if oc!=ones:
            res|=(1<<bit)
    print(res)