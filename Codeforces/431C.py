from functools import cache
total_weight,k,edgeD=list(map(int,input().split()))
@cache
def dfs(distance,goodEdge):
    global total_weight,k,edgeD
    if distance==total_weight:
        return int(goodEdge)
    res=0
    for i in range(1,k+1):
        if distance+i>total_weight: break
        res+=dfs(distance+i,goodEdge or i>=edgeD)
    return res
print(dfs(0,False)%(10**9+7))