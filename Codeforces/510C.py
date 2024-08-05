from collections import defaultdict
num_names=int(input())
names=[input() for _ in range(num_names)]
charMap=defaultdict(set) #maps all characters to characters coming before it
for i in range(len(names)-1):
    p1=p2=0
    while p1<len(names[i]) and p2<len(names[i+1]):
        if names[i][p1]!=names[i+1][p2]:
            charMap[names[i+1][p2]].add(names[i][p1])
            break
        p1+=1
        p2+=1
    else:
        if len(names[i])>len(names[i+1]):
            print('Impossible')
            exit()
indegree=[0]*26
need={chr(i+97) for i in range(26)}
res=[]
def dfs(char):
    if indegree[ord(char)-97]==1:
        print('Impossible')
        exit()
    indegree[ord(char)-97]=1
    for neighbor in charMap[char]:
        if indegree[ord(neighbor)-97]==2:
            continue
        dfs(neighbor)
    res.append(char)
    indegree[ord(char)-97]=2
    need.discard(char)
for key in list(charMap.keys()):
    if indegree[ord(key)-97]==0:
        dfs(key)
for char in need:
    res.append(char)
print(''.join(res))

 