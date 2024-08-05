import sys
from functools import cache
def input():
    return sys.stdin.readline().rstrip('\r\n')
n=input()
@cache
def digit_dp(number,index,tight,x,y,leading_zero):
    if index==len(number):
        return int(not leading_zero)
    res=0
    if x==-1:
        limit=int(number[index]) if tight else 9
        for i in range(limit+1):
            if i==0 and leading_zero:
                res+=digit_dp(number,index+1,False,-1,-1,True)
                continue
            res+=digit_dp(number,index+1,tight and i==limit,i,-1,False)
    elif y==-1:
        limit=int(number[index]) if tight else 9
        for i in range(limit+1):
            if i==x:
                res+=digit_dp(number,index+1,tight and i==limit,i,-1,False)
                continue
            res+=digit_dp(number,index+1,tight and i==limit,x,i,False)
    else:
        limit=int(number[index]) if tight else 9
        if x<=limit:
            res+=digit_dp(number,index+1,tight and x==limit,x,y,False)
        if y<=limit:
            res+=digit_dp(number,index+1,tight and y==limit,x,y,False)
    return res
print(digit_dp(n,0,True,-1,-1,True))