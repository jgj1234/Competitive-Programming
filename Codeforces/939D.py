class UnionFind:
    def __init__(self):
        self.par=[-1]*26
        self.rank=[0]*26
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
        if self.rank[uPar]==self.rank[vPar]:
            self.rank[uPar]+=1
        if self.rank[uPar]>=self.rank[vPar]:
            self.par[vPar]=uPar
        else:
            self.par[uPar]=vPar
        return True
n=int(input())
s1=input()
s2=input()
uf=UnionFind()
changes=[]
for i in range(len(s1)):
    if s1[i]!=s2[i]:
        if uf.union(ord(s1[i])-97,ord(s2[i])-97):
            changes.append([s1[i],s2[i]])
print(len(changes))
for change in changes:
    print(' '.join(change))