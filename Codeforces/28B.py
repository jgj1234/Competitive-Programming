class UnionFind:
    def __init__(self, n):
        self.par=[-1]*n
        self.rank=[0]*n
    def find(self,u):
        if self.par[u]==-1:
            return u
        self.par[u]=self.find(self.par[u])
        return self.par[u]
    def union(self,u,v):
        uPar=self.find(u)
        vPar=self.find(v)
        if uPar==vPar: return
        if self.rank[uPar]==self.rank[vPar]:
            self.rank[uPar]+=1
        if self.rank[uPar]>=self.rank[vPar]:
            self.par[vPar]=uPar
        else:
            self.par[uPar]=vPar
def zeroindex(num):
    return int(num)-1
num_cells=int(input())
permutation=list(map(zeroindex,input().split()))
wanted=list(map(int,input().split()))
uf=UnionFind(num_cells)
for i in range(len(wanted)):
    if i+wanted[i]<len(wanted):
        uf.union(i,i+wanted[i])
    if i-wanted[i]>=0:
        uf.union(i,i-wanted[i])
for i in range(len(permutation)):
    if uf.find(permutation[i])!=uf.find(i):
        print('NO')
        break
else:
    print('YES')