from collections import deque

def bfs_fire(fire_queue, fire_time, R, C):
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    while fire_queue:
        x, y = fire_queue.popleft()
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if 0 <= nx < R and 0 <= ny < C and fire_time[nx][ny] == -1 and maze[nx][ny] != '#':
                fire_time[nx][ny] = fire_time[x][y] + 1
                fire_queue.append((nx, ny))

def bfs_jihun(jihun_queue, jihun_time, fire_time, R, C):
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    while jihun_queue:
        x, y = jihun_queue.popleft()
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if 0 <= nx < R and 0 <= ny < C:
                if maze[nx][ny] == '.' and jihun_time[nx][ny] == -1:
                    if fire_time[nx][ny] == -1 or jihun_time[x][y] + 1 < fire_time[nx][ny]:
                        jihun_time[nx][ny] = jihun_time[x][y] + 1
                        jihun_queue.append((nx, ny))
                        if nx == 0 or ny == 0 or nx == R-1 or ny == C-1:
                            return jihun_time[nx][ny] + 1
    return "IMPOSSIBLE"

R, C = map(int, input().split())
maze = [list(input().strip()) for _ in range(R)]

fire_queue = deque()
jihun_queue = deque()
fire_time = [[-1] * C for _ in range(R)]
jihun_time = [[-1] * C for _ in range(R)]

for i in range(R):
    for j in range(C):
        if maze[i][j] == 'F':
            fire_queue.append((i, j))
            fire_time[i][j] = 0
        elif maze[i][j] == 'J':
            jihun_queue.append((i, j))
            jihun_time[i][j] = 0
            if i == 0 or j == 0 or i == R-1 or j == C-1:
                print(1)
                exit()

bfs_fire(fire_queue, fire_time, R, C)
result = bfs_jihun(jihun_queue, jihun_time, fire_time, R, C)
print(result)