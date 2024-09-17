from collections import deque
import sys
input = sys.stdin.read

def solve(n, m, data):
    horse = []
    dx = [-2, -2, -1, -1, 1, 1, 2, 2]
    dy = [-1, 1, 2, -2, -2, 2, -1, 1]

    for i in range(n):
        for j in range(m):
            if data[i][j] != '.':
                horse.append((i, j, int(data[i][j])))

    answer = [[0] * m for _ in range(n)]
    malcount = [[0] * m for _ in range(n)]

    for x, y, val in horse:
        q = deque([(x, y, val, 1)])
        visited = [[False] * m for _ in range(n)]
        visited[x][y] = True
        malcount[x][y] += 1

        while q:
            x, y, val1, count = q.popleft()
            if val1 == 0:
                val1 = val
                count += 1
            for i in range(8):
                nx, ny = x + dx[i], y + dy[i]
                if 0 <= nx < n and 0 <= ny < m and not visited[nx][ny]:
                    q.append((nx, ny, val1 - 1, count))
                    malcount[nx][ny] += 1
                    visited[nx][ny] = True
                    answer[nx][ny] += count

    min_value = float('inf')
    for i in range(n):
        for j in range(m):
            if malcount[i][j] == len(horse):
                min_value = min(min_value, answer[i][j])

    if len(horse) == 1:
        print(0)
    elif min_value == float('inf'):
        print(-1)
    else:
        print(min_value)

if __name__ == "__main__":
    input_data = input().splitlines()
    n, m = map(int, input_data[0].split())
    data = [list(line) for line in input_data[1:]]
    solve(n, m, data)