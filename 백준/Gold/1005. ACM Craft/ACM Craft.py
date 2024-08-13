from collections import deque
import io, os
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
def dfs(node):
    if build[node] != -1:   return build[node]
    max = 0
    for con_node in order[node]:
        build_t = dfs(con_node)
        if build_t > max:   max = build_t

    build[node] = max + D[node]
    return build[node]
T = int(input())
while T:
    N, K = map(int, input().split())
    D = list(map(int, input().split()))
    order = [list() for _ in range(N)]
    for i in range(K):
        X, Y = map(lambda x:x-1, list(map(int, input().split())))
        order[Y].append(X)
    W = int(input()) - 1
    build = [-1 for _ in range(N)]
    print(dfs(W))
    T -= 1