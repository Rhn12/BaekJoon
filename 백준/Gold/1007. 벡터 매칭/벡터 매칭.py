import os
import sys
from itertools import combinations

def main(f=None):
    init(f)

    def min_vec(l):
        x_n, y_n = x_t, y_t
        for x, y in l:
            x_n -= 2*x
            y_n -= 2*y
        return x_n ** 2 + y_n ** 2

    tc = int(input().strip())
    for _ in range(tc):
        n = int(input().strip())
        crd = []
        x_t, y_t = (-int(i) for i in input().split())
        for _ in range(n-1):
            x, y = map(int, input().split())
            x_t += x
            y_t += y
            crd.append((x, y))

        ans = int(8e10)

        for i in combinations(crd, n//2-1):
            ans = min(ans, min_vec(i))
        print(pow(ans, 0.5))

enu = enumerate

def For(*args):
    return itertools.product(*map(range, args))
def Mat(h, w, default=None):
    return [[default for _ in range(w)] for _ in range(h)]
def nDim(*args, default=None):
    if len(args) == 1:
        return [default for _ in range(args[0])]
    else:
        return [nDim(*args[1:], default=default) for _ in range(args[0])]
def setStdin(f):
    global DEBUG, input
    DEBUG = True
    sys.stdin = open(f)
    input = sys.stdin.readline
def init(f=None):
    global input
    input = sys.stdin.readline
    if os.path.exists("o"):
        sys.stdout = open("o", "w")
    if f is not None:
        setStdin(f)
    else:
        if len(sys.argv) == 1:
            if os.path.isfile("in/i"):
                setStdin("in/i")
            elif os.path.isfile("i"):
                setStdin("i")
        elif len(sys.argv) == 2:
            setStdin(sys.argv[1])
        else:
            assert False, "Too many sys.argv: %d" % len(sys.argv)
def pr(*args):
    if DEBUG:
        print(*args)
def pfast(*args, end="\n", sep=' '):
    sys.stdout.write(sep.join(map(str, args)) + end)
def parr(arr):
    for i in arr:
        print(i)

if __name__ == "__main__":
    main()