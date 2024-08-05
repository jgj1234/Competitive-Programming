def digit_dp(index,number,tight,nonzeros,memo):
    if index==len(number):
        return 1
    if (index,tight,nonzeros) in memo:
        return memo[(index,tight,nonzeros)]
    res=0
    if nonzeros<3:
        upper_limit=int(number[index]) if tight else 9
        for i in range(upper_limit+1):
            new_tight=tight and int(number[index])==i
            new_nz=nonzeros+int(i!=0)
            res+=digit_dp(index+1,number,new_tight,new_nz,memo)
    else:
        res+=digit_dp(index+1,number,False,3,memo)
    memo[(index,tight,nonzeros)]=res
    return res
def solve(L,R):
    memoL={}
    memoR={}
    return digit_dp(0,str(R),True,0,memoL)-digit_dp(0,str(L-1),True,0,memoR)
num_tests=int(input())
for i in range(num_tests):
    left,right=list(map(int,input().split()))
    print(solve(left,right))