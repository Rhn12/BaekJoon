def squareNoNo(n, mobius):

    p = 0

    for i in range(1, int(n ** 0.5) + 1, 1):

        p += mobius[i] * (n // (i * i))

    return p

def calculate_mobius(n):

    mobius = [0] * (n + 1)

    mobius[1] = 1

    for i in range(1, n + 1):

        if mobius[i]:

            for j in range(i * 2, n + 1, i):

                mobius[j] -= mobius[i]

    return mobius

def binary_search(l, r, k, mobius):

    while l < r - 1:

        mid = (l + r) // 2

        if squareNoNo(mid, mobius) < k:

            l = mid

        else:

            r = mid

    return r

k = int(input())

mobius = calculate_mobius(1000000)

result = binary_search(0, 2000000000, k, mobius)

print(result)