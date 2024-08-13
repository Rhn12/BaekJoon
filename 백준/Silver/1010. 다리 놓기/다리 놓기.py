import math

def calculate_combinations(n, m):
    return math.comb(m, n)

T = int(input().strip())
test_cases = []

for _ in range(T):
    N, M = map(int, input().strip().split())
    test_cases.append((N, M))

for N, M in test_cases:
    result = calculate_combinations(N, M)
    print(result)