def flip_3x3(matrix, x, y):
    for i in range(3):
        for j in range(3):
            matrix[x + i][y + j] = 1 - matrix[x + i][y + j]

def min_operations_to_transform(N, M, A, B):
    if N < 3 or M < 3:
        # N이나 M이 3보다 작은 경우, 3x3 변환이 불가능하기 때문에 비교만으로 결과 결정
        return 0 if A == B else -1
    
    operations = 0
    
    # A와 B가 다르면 3x3 매트릭스 뒤집기
    for i in range(N - 2):
        for j in range(M - 2):
            if A[i][j] != B[i][j]:
                flip_3x3(A, i, j)
                operations += 1
    
    # 변환 후 A와 B가 같은지 확인
    if A == B:
        return operations
    else:
        return -1

# 입력 받기
N, M = map(int, input().split())
A = [list(map(int, input().strip())) for _ in range(N)]
B = [list(map(int, input().strip())) for _ in range(N)]

# 결과 출력
print(min_operations_to_transform(N, M, A, B))