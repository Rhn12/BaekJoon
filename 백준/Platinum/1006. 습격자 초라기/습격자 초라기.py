import sys

a, b, c = [None]*10001, [None]*10001, [None]*10001
e = []
n, w, res = None, None, None

def solve(start):
    for i in range(start, n):
        a[i+1] = min(b[i]+1, c[i]+1)
        if e[0][i] + e[1][i] <= w:
            a[i+1] = min(a[i+1], a[i]+1)
        if i>0 and e[0][i-1]+e[0][i] <= w and e[1][i-1]+e[1][i] <= w:
            a[i+1] = min(a[i+1], a[i-1]+2)
        if i < n-1:
            b[i+1] = a[i+1]+1
            if e[0][i]+e[0][i+1] <= w:
                b[i+1] = min(b[i+1], c[i]+1)
            c[i+1] = a[i+1]+1
            if e[1][i]+e[1][i+1] <= w:
                c[i+1] = min(c[i+1], b[i]+1)

t = int(sys.stdin.readline())

for _ in range(t):
    n, w = map(int, sys.stdin.readline().split())
    res = 30000
    e = []
    for __ in range(2):
        l = list(map(int, sys.stdin.readline().split()))
        e.append(l)
    a[0], b[0], c[0] = 0, 1, 1
    solve(0)
    res = min(res, a[n])
    if n>1 and e[0][0]+e[0][n-1] <= w and e[1][0]+e[1][n-1] <= w:
        a[1], b[1], c[1] = 0, 1, 1
        solve(1)
        res = min(res, a[n-1]+2)
    if n>1 and e[0][0]+e[0][n-1] <= w:
        a[1], b[1] = 1, 2
        c[1] = 1 if e[1][0]+e[1][1]<=w else 2
        solve(1)
        res = min(res, c[n-1]+1)
    if n>1 and e[1][0]+e[1][n-1] <= w:
        a[1], c[1] = 1, 2
        b[1] = 1 if e[0][0]+e[0][1]<=w else 2
        solve(1)
        res = min(res, b[n-1]+1)
    print(res)