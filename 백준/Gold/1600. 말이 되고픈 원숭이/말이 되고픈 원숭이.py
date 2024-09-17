from collections import deque

# 4가지 인접 이동(상, 하, 좌, 우)
dx = [0, 0, -1, 1]
dy = [-1, 1, 0, 0]

# 말의 이동(나이트 이동, 8방향)
horse_dx = [-2, -2, -1, -1, 1, 1, 2, 2]
horse_dy = [-1, 1, -2, 2, -2, 2, -1, 1]

def bfs(K, W, H, board):
    # 방문 여부를 저장하는 3차원 배열: visited[y][x][k] => (x, y) 위치에 남은 말 이동 횟수가 k일 때 방문 여부
    visited = [[[False] * (K + 1) for _ in range(W)] for _ in range(H)]
    queue = deque([(0, 0, 0, K)])  # (x, y, 이동 횟수, 남은 말 이동 횟수)
    visited[0][0][K] = True

    while queue:
        x, y, moves, remaining_moves = queue.popleft()

        # 도착점에 도달하면 이동 횟수를 반환
        if x == W - 1 and y == H - 1:
            return moves

        # 일반적인 인접한 칸으로 이동
        for i in range(4):
            nx, ny = x + dx[i], y + dy[i]
            if 0 <= nx < W and 0 <= ny < H and board[ny][nx] == 0 and not visited[ny][nx][remaining_moves]:
                visited[ny][nx][remaining_moves] = True
                queue.append((nx, ny, moves + 1, remaining_moves))

        # 말의 이동 (최대 K번)
        if remaining_moves > 0:
            for i in range(8):
                nx, ny = x + horse_dx[i], y + horse_dy[i]
                if 0 <= nx < W and 0 <= ny < H and board[ny][nx] == 0 and not visited[ny][nx][remaining_moves - 1]:
                    visited[ny][nx][remaining_moves - 1] = True
                    queue.append((nx, ny, moves + 1, remaining_moves - 1))

    # 도착점에 도달할 수 없으면 -1 반환
    return -1

def main():
    K = int(input().strip())
    W, H = map(int, input().strip().split())
    board = [list(map(int, input().strip().split())) for _ in range(H)]
    result = bfs(K, W, H, board)
    print(result)

if __name__ == "__main__":
    main()