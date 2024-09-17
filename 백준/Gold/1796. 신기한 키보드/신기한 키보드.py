import sys
import math

def dist(a, b, c, d):
    if c == -1 or d == -1:
        return 0
    A = abs(a - c)
    B = abs(c - d)
    C = abs(d - b)
    return A + B + C

def solve(alpha, pos):
    if alpha == 26:
        return 0
    if cache[alpha][pos] != -1:
        return cache[alpha][pos]
    ret = math.inf
    posl = lo[alpha]
    posr = hi[alpha]
    
    if exist[alpha]:
        for i in range(s):
            ret = min(ret, solve(alpha + 1, i) + min(dist(pos, i, posl, posr), dist(pos, i, posr, posl)))
    else:
        ret = solve(alpha + 1, pos)
    
    cache[alpha][pos] = ret
    return ret

if __name__ == "__main__":
    input = sys.stdin.read
    S = input().strip()
    s = len(S)
    cache = [[-1] * 1001 for _ in range(26)]
    lo = [math.inf] * 27
    hi = [-1] * 27
    exist = [False] * 26

    for i in range(26):
        for j in range(s):
            if ord(S[j]) - ord('a') == i:
                exist[i] = True
                lo[i] = min(lo[i], j)
                hi[i] = max(hi[i], j)
    
    ret = solve(0, 0)
    print(ret + s)