class UnionFind:
    def __init__(self,arr):
        self.par=[-1]*len(arr)
        self.rank=[0]*len(arr)
        self.sums=arr
        self.res=0
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
            self.sums[uPar]+=self.sums[vPar]
            self.res=max(self.res,self.sums[uPar])
        else:
            self.par[uPar]=vPar
            self.sums[vPar]+=self.sums[uPar]
            self.res=max(self.res,self.sums[vPar])
    def updateNumber(self,pos,number):
        self.sums[pos]=number
        self.res=max(self.res,self.sums[pos])
        if pos>0 and self.sums[pos-1]!=-1:
            self.union(pos,pos-1)
        if pos+1<len(self.sums) and self.sums[pos+1]!=-1:
            self.union(pos,pos+1)
n=int(input())
nums=list(map(int,input().split()))
permutation=list(map(int,input().split()))
queries=[]
for i in range(len(permutation)):
    queries.append([permutation[i]-1,nums[permutation[i]-1]])
    nums[permutation[i]-1]=-1
uf=UnionFind(nums)
for i in range(1,len(nums)):
    if nums[i]!=-1 and nums[i-1]!=-1:
        uf.union(i,i-1)
r=[]
for i in range(len(queries)-1,-1,-1):
    r.append(uf.res)
    uf.updateNumber(queries[i][0],queries[i][1])
for i in range(len(r)-1,-1,-1):
    print(r[i])