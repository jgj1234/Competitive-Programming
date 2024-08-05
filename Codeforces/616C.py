class UnionFind:
    def __init__(self,grid):
        self.par=[-1]*(len(grid)*len(grid[0]))
        self.size=[0]*(len(grid)*len(grid[0]))
        for i in range(len(grid)):
            for j in range(len(grid[0])):
                if grid[i][j]=='.':
                    key=i*len(grid[0])+j
                    self.size[key]=1
                    self.par[key]=key
    def find(self,key):
        if self.par[key]==key:
            return key
        self.par[key]=self.find(self.par[key])
        return self.par[key]
    def union(self,i,j):
        iPar=self.find(i)
        jPar=self.find(j)
        if iPar==jPar:
            return
        if self.size[iPar]>self.size[jPar]:
            self.par[jPar]=iPar
            self.size[iPar]+=self.size[jPar]
        else:
            self.par[iPar]=jPar
            self.size[jPar]+=self.size[iPar]
num_rows,num_cols=list(map(int,input().split()))
matrix=[]
for _ in range(num_rows):
    matrix.append([x for x in input()])
uf=UnionFind(matrix)
for i in range(len(matrix)):
    for j in range(len(matrix[0])):
        if matrix[i][j]=='.':
            key=i*len(matrix[0])+j
            for dr,dc in [(i-1,j),(i,j-1)]:
                if dr>=0 and dc>=0 and matrix[dr][dc]=='.':
                    uf.union(key,dr*len(matrix[0])+dc)
for i in range(len(matrix)):
    for j in range(len(matrix[0])):
        if matrix[i][j]=='*':
            combo=1
            keys=set()
            for dr, dc in [(i+1,j),(i-1,j),(i,j-1),(i,j+1)]:
                if 0<=dr<len(matrix) and 0<=dc<len(matrix[0]) and matrix[dr][dc]=='.':
                    keys.add(uf.find(dr*len(matrix[0])+dc))
            for key in keys:
                combo+=uf.size[key]
            matrix[i][j]=str(combo%10)
for row in matrix:
    print(''.join(row))