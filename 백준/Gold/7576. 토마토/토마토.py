from collections import deque

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]

def bfs():
    while queue:
        x, y = queue.popleft()
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if 0 <= nx < N and 0 <= ny < M and tomato[nx][ny] == 0:
                tomato[nx][ny] = tomato[x][y] + 1
                queue.append((nx, ny))

M, N = map(int, input().split())
tomato = []
queue = deque()

for i in range(N):
    row = list(map(int, input().split()))
    tomato.append(row)
    for j in range(M):
        if row[j] == 1:
            queue.append((i, j))

bfs()

max_days = 0
for row in tomato:
    if 0 in row:
        print(-1)
        exit()
    max_days = max(max_days, max(row))

print(max_days - 1)