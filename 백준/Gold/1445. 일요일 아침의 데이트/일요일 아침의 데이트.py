import sys
from collections import deque

input = sys.stdin.readline

def sol(flag, y, x, ny, nx):
    i, j = ((0, 0), (1, 0), (0, 0), (0, 1))[flag]

    if ct[ny][nx] > ct[y][x] + i or (ct[ny][nx] == ct[y][x] + i and cat[ny][nx] > cat[y][x] + j):
        ct[ny][nx] = ct[y][x] + i
        cat[ny][nx] = cat[y][x] + j
        dq.append((ny, nx))

if __name__ == "__main__":
    n, m = map(int, input().split())
    maps = [list(input().strip()) for _ in range(n)]
    ct = [[2500] * m for _ in range(n)]
    cat = [[2500] * m for _ in range(n)]
    dir = [(-1, 0), (0, 1), (1, 0), (0, -1)]

    dq = deque()

    for y in range(n):
        for x in range(m):
            if maps[y][x] == 'S':
                dq.append((y, x))
                ct[y][x] = cat[y][x] = 0
            elif maps[y][x] == 'F':
                out_y, out_x = y, x
            elif maps[y][x] == '.':
                for dy, dx in dir:
                    ny, nx = y + dy, x + dx
                    if 0 <= ny < n and 0 <= nx < m and maps[ny][nx] == 'g':
                        maps[y][x] = 'a'
                        break

    while dq:
        y, x = dq.popleft()

        for dy, dx in dir:
            ny, nx = y + dy, x + dx
            if 0 <= ny < n and 0 <= nx < m:
                if maps[ny][nx] == 'g':
                    sol(1, y, x, ny, nx)
                elif maps[ny][nx] == '.':
                    sol(2, y, x, ny, nx)
                elif maps[ny][nx] == 'a':
                    sol(3, y, x, ny, nx)
                elif maps[ny][nx] == 'F':
                    sol(0, y, x, ny, nx)

    print(ct[out_y][out_x], cat[out_y][out_x])
