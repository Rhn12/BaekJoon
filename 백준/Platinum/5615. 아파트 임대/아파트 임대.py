import sys

def miller_rabin(n, a):
    d = (n - 1) // 2
    while d % 2 == 0:
        if pow(a, d, n) == n - 1:
            return True
        d //= 2
    tmp = pow(a, d, n)
    return tmp == n - 1 or tmp == 1

def main():
    t = int(input())
    alist = [2, 7, 61]
    cnt = 0
    for _ in range(t):
        n = int(sys.stdin.readline().strip()) * 2 + 1
        if n % 2 == 1:
            for a in alist:
                if not miller_rabin(n, a):
                    if n in alist:
                        cnt += 1
                    break
                if a == 61:
                    cnt += 1
    print(cnt)

if __name__ == "__main__":
    main()