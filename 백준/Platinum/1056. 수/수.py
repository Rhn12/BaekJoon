from math import log2, ceil, floor

dp = {1 : 0, 2 : 1, 3 : 2}

def solve(n):
    if n in dp:
        return dp[n]

    min_steps = float('inf')

    for i in range(2, ceil(log2(n)) + 1):
        j = n ** (1 / i)
        m = floor(j)
        M = ceil(j)

        dm = abs(n - m ** i)
        dM = abs(n - M ** i)

        if dm < dM:
            min_steps = min(min_steps, solve(m) + dm)
        else:
            min_steps = min(min_steps, solve(M) + dM)

    dp[n] = min_steps + 1
    return dp[n]

n = int(input())
print(solve(n))