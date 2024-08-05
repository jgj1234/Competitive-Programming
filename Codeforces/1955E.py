from collections import deque, Counter,defaultdict
from typing import List
def check(string,length):
    changes=[0]*len(string)
    for i in range(len(string)-length+1):
        if i>0: changes[i]+=changes[i-1]
        if (changes[i]%2==0 and string[i]=='0') or (changes[i]%2==1 and string[i]=='1'):
            changes[i]+=1
            if i+length<len(changes):
                changes[i+length]-=1
    for i in range(len(string)-length+1,len(string)):
        changes[i]+=changes[i-1]
        if (changes[i]%2==0 and string[i]=='0') or (changes[i]%2==1 and string[i]=='1'):
            return False
    return True
for case in range(int(input())):
    n=int(input())
    s=input()
    for i in range(n,0,-1):
        if check(s,i):
            print(i)
            break