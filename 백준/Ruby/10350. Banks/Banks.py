from sys import stdin
import math

n = int(stdin.readline().strip())
arr = list(map(int, stdin.readline().split()))
partial_sum = [0]
for i in range(2 * n):
    partial_sum.append(partial_sum[-1] + arr[i % n])

result = 0
for i in range(n - 1):
    for j in range(1, n + 1):
        if partial_sum[j + i] < partial_sum[j - 1]:
            result += math.ceil(abs(partial_sum[j + i] - partial_sum[j - 1]) / partial_sum[n])

print(result)