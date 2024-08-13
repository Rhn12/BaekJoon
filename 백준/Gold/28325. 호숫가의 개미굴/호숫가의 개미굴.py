n = int(input())
a = list(map(int, input().split()))
def solve(a):
    t = sum(a)
    if t == 0:
        return n//2
    i = 0
    for i, b in enumerate(a):
        if b:
            break
    a = a[i+1:] + a[:i+1]
    c = [0]*n
    for _ in range(n):
        if a[_] or c[_]:
            continue
        for j in range(_, n):
            if a[j]:
                break
            c[j] = 1
        t += (j-_+1)//2
    return t
print(solve(a))