def min_cost_to_paint_houses(n, costs):
    # dp 배열을 초기화 합니다. dp[i][j]는 i번째 집을 j색으로 칠할 때의 최소 비용을 나타냅니다.
    dp = [[0] * 3 for _ in range(n)]

    # 첫 번째 집의 비용을 초기화합니다.
    dp[0][0] = costs[0][0]
    dp[0][1] = costs[0][1]
    dp[0][2] = costs[0][2]

    # dp를 채워나갑니다.
    for i in range(1, n):
        dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + costs[i][0]
        dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + costs[i][1]
        dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + costs[i][2]

    # 마지막 집을 칠하는 데 드는 최소 비용을 반환합니다.
    return min(dp[n-1][0], dp[n-1][1], dp[n-1][2])

# 입력을 받습니다.
n = int(input())
costs = []
for _ in range(n):
    costs.append(list(map(int, input().split())))

# 결과를 출력합니다.
print(min_cost_to_paint_houses(n, costs))