def count_handshakes(N):
    MOD = 987654321
    dp = [0] * (N // 2 + 1)
    dp[0] = 1  # Base case: C_0 = 1
    for n in range(1, N // 2 + 1):
        for i in range(n):
            dp[n] = (dp[n] + dp[i] * dp[n - 1 - i]) % MOD
    return dp[N // 2]

N = int(input().strip())
result = count_handshakes(N)
print(result)