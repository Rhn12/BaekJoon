import sys
input = sys.stdin.readline
sys.setrecursionlimit(10**5)

def dfs(node, cnt):
    if cnt == 5:
        print(1)
        exit()  # 프로그램 끝내기
    visited[node] = True
    for i in a[node]:
        if not visited[i]:
            dfs(i, cnt + 1)
    visited[node] = False  # 백트래킹

V, E = map(int, input().split())
a = [[] for _ in range(V)]
visited = [False] * V

for _ in range(E):
    u, v = map(int, input().split())
    a[u].append(v)
    a[v].append(u)

for i in range(V):
    dfs(i, 1)
    visited[i] = False  # 초기화

print(0)