from collections import deque

def bfs_escape_maze(maze, start, N, M):
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    queue = deque([(start[0], start[1], 0, 0)])
    visited = [[[False] * (1 << 6) for _ in range(M)] for _ in range(N)]
    visited[start[0]][start[1]][0] = True
    
    while queue:
        x, y, steps, keys = queue.popleft()
        
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if 0 <= nx < N and 0 <= ny < M and not visited[nx][ny][keys]:
                cell = maze[nx][ny]
                
                if cell == '#':
                    continue
                
                if cell == '1':
                    return steps + 1
                
                if 'a' <= cell <= 'f':
                    new_keys = keys | (1 << (ord(cell) - ord('a')))
                    if not visited[nx][ny][new_keys]:
                        visited[nx][ny][new_keys] = True
                        queue.append((nx, ny, steps + 1, new_keys))
                
                elif 'A' <= cell <= 'F':
                    if keys & (1 << (ord(cell) - ord('A'))):
                        visited[nx][ny][keys] = True
                        queue.append((nx, ny, steps + 1, keys))
                
                else:
                    visited[nx][ny][keys] = True
                    queue.append((nx, ny, steps + 1, keys))
    
    return -1

def main():
    N, M = map(int, input().split())
    maze = []
    start = None
    
    for i in range(N):
        row = input().strip()
        maze.append(row)
        if '0' in row:
            start = (i, row.index('0'))
    
    print(bfs_escape_maze(maze, start, N, M))

if __name__ == "__main__":
    main()