import sys,math
def input():
    return sys.stdin.readline().rstrip('\r\n')
t=int(input())
for _ in range(t):
    n,x=map(int,input().split())
    res=n
    ans=False
    done=False
    minRange=float('inf')
    for i in range(64,-1,-1):
        nBit=bool(n&(1<<i))
        xBit=bool(x&(1<<i))
        if not nBit and xBit or (done and nBit and xBit):
            ans=True
            break
        elif nBit and xBit:
            minRange=min(minRange,n+(2**i-n%2**i)-1)
        elif not done and nBit and not xBit:
            length=2**i
            res=n+(length-n%length)
            done=True
    if not ans and res<=minRange:
        print(res)
    else:
        print(-1)