from functools import cache
@cache
def digit_dp(string,index,tight,lastdigit):
    if index==len(string):
        return 1
    ub=int(string[index]) if tight else 9
    res=0
    for i in range(ub+1):
        if i==0 and lastdigit==-1:
            res+=digit_dp(string,index+1,False,-1)
            continue
        if i==lastdigit: continue
        res+=digit_dp(string,index+1,tight and i==ub,i)
    return res
left,right=list(map(int,input().split()))
if left!=0:
    print(digit_dp(str(right),0,True,-1)-digit_dp(str(left-1),0,True,-1))
else:
    print(digit_dp(str(right),0,True,-1))
