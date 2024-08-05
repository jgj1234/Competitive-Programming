from collections import defaultdict
class UnionFind:
    def __init__(self,n):
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
size=int(input())
permutation=list(map(int,input().split()))
matrix=[]
for i in range(size):
    matrix.append(input())
uf=UnionFind(size)
for i in range(len(matrix)):
    for j in range(i,len(matrix[0])):
        if matrix[i][j]=='1':
            uf.union(i,j)
rootMap=defaultdict(list)
for i in range(len(permutation)):
    root=uf.find(i)
    rootMap[root].append(permutation[i])
for key in rootMap:
    rootMap[key].sort(reverse=True)
res=[0]*len(permutation)
for i in range(len(res)):
    res[i]=rootMap[uf.find(i)].pop()
print(*res)