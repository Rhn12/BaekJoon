from collections import deque

def bfs(field, x, y, n, m):
    queue = deque([(x, y)])
    field[y][x] = 0  # 방문 처리

    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # 상, 하, 좌, 우 방향
    while queue:
        cx, cy = queue.popleft()
        for dx, dy in directions:
            nx, ny = cx + dx, cy + dy
            if 0 <= nx < m and 0 <= ny < n and field[ny][nx] == 1:
                field[ny][nx] = 0  # 방문 처리
                queue.append((nx, ny))

def count_cabbage_clusters(n, m, positions):
    field = [[0] * m for _ in range(n)]
    for x, y in positions:
        field[y][x] = 1
    
    worm_count = 0
    for y in range(n):
        for x in range(m):
            if field[y][x] == 1:
                bfs(field, x, y, n, m)
                worm_count += 1
    
    return worm_count

# 입력 받기
t = int(input())
results = []

for _ in range(t):
    m, n, k = map(int, input().split())
    positions = [tuple(map(int, input().split())) for _ in range(k)]
    results.append(count_cabbage_clusters(n, m, positions))

# 결과 출력
for result in results:
    print(result)