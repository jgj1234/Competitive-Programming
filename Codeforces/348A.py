n=int(input())
nums=list(map(int,input().split()))
def works(games):
    pos=0
    for num in nums:
        pos+=max(0,games-num)
    return pos>=games
lp=max(nums)
rp=sum(nums)
ans=0
while lp<=rp:
    mid=(lp+rp)//2
    if works(mid):
        rp=mid-1
    else:
        lp=mid+1
print(lp)