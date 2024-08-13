M = 500001
mu = [0] * M
mu[1] = 1

def sieve():
    for i in range(1, M):
        for j in range(2 * i, M, i):
            mu[j] -= mu[i]

sieve()

def f(n):
    res = n
    i = 1
    while i * i <= n:
        res -= mu[i] * (n // (i * i))
        i += 1
    return res

def find_k(k):
    left, right = 0, M * M
    while left < right:
        mid = (left + right) // 2
        if f(mid) >= k:
            right = mid
        else:
            left = mid + 1
    return left

def main():
    k = int(input())
    result = find_k(k)
    print(result)

if __name__ == "__main__":
    main()