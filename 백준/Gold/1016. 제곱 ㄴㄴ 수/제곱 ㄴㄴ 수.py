def count_square_free_numbers(min_val, max_val):
    # 범위의 길이
    range_length = max_val - min_val + 1
    
    # 제곱ㄴㄴ수를 체크하기 위한 배열 초기화 (True로 초기화)
    is_square_free = [True] * range_length
    
    # 2 이상의 모든 제곱수를 구함
    max_sqrt = int(max_val**0.5) + 1
    
    for i in range(2, max_sqrt):
        square = i * i
        # min_val 이상에서 square로 나누어 떨어지는 첫 숫자를 찾음
        start = ((min_val + square - 1) // square) * square
        
        for j in range(start, max_val + 1, square):
            is_square_free[j - min_val] = False
    
    # 제곱ㄴㄴ수의 개수를 셈
    count = sum(is_square_free)
    return count

# 입력 받기
min_val, max_val = map(int, input().split())

# 결과 계산
result = count_square_free_numbers(min_val, max_val)

# 결과 출력
print(result)