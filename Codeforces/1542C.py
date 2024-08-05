from math import lcm
for case in range(int(input())):
    n = int(input())
    res = 0
    MOD = 10**9+7
    l = 1
    for i in range(2,101):
        occ = n//l
        l = lcm(l,i)
        occ2 = n//l
        res+=i*(occ-occ2)
        res%=MOD
    print(res)