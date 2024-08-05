class UnionFind:
    def __init__(self,n):
        self.par=[-1]*n
        self.rank=[0]*n
        self.redundant=[False]*n
        self.cc=n
    def find(self,u):
        if self.par[u]==-1:
            return u
        self.par[u]=self.find(self.par[u])
        return self.par[u]
    def union(self,u,v):
        uPar=self.find(u)
        vPar=self.find(v)
        if uPar==vPar:
            return False
        self.cc-=1
        if self.rank[uPar]==self.rank[vPar]:
            self.rank[uPar]+=1
        if self.rank[uPar]>=self.rank[vPar]:
            self.par[vPar]=uPar
            self.redundant[uPar]=self.redundant[uPar] or self.redundant[vPar]
        else:
            self.par[uPar]=vPar
            self.redundant[vPar]=self.redundant[vPar] or self.redundant[uPar]
        return True
def mapper(num):
    return int(num)-1
num_tests=int(input())
for _ in range(num_tests):
    #maximum # of round dances is number of connected components
    n=int(input())
    nums=list(map(mapper,input().split()))
    uf=UnionFind(n)
    for i in range(len(nums)):
        if nums[i]<i and nums[nums[i]]==i:
            continue
        if not uf.union(i,nums[i]):
            uf.redundant[uf.find(i)]=True
    if uf.cc==1:
        print(1,1)
    else:
        count=0
        add=False
        for i in range(len(uf.par)):
            if uf.par[i]==-1:
                if uf.redundant[i]:
                    count+=1
                else:
                    add=True
        print(count+add,uf.cc)