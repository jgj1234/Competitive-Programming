from collections import Counter

recipe = Counter(input())
cb,cc,cs=recipe['B'], recipe['C'],recipe['S']
b, s, c = list(map(int, input().split()))
pb, ps, pc = list(map(int, input().split()))
money = int(input())

lp = 0
rp = money+1000
ans = 0
while lp <= rp:
    mid = (lp + rp) // 2  # num hamburgers
    bCost = max(0, (cb * mid - b)) * pb
    cCost = max(0, (cc * mid - c)) * pc
    sCost = max(0, (cs * mid - s)) * ps
    total = bCost + cCost + sCost
    if total == money:
        print(mid)
        exit()
    if total > money:
        rp = mid - 1
    else:
        lp = mid + 1
        ans = mid

print(ans)