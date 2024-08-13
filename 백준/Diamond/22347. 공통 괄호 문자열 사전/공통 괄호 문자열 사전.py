def is_valid_parentheses(s):
    stack = 0
    for char in s:
        if char == '(':
            stack += 1
        elif char == ')':
            stack -= 1
            if stack < 0:
                return False
    return stack == 0
def generate_valid_substrings(s):
    valid_substrings = set()
    n = len(s)
    for start in range(n):
        stack = 0
        for end in range(start, n):
            if s[end] == '(':
                stack += 1
            elif s[end] == ')':
                stack -= 1
            if stack < 0:
                break
            substring = s[start:end + 1]
            if stack == 0:
                valid_substrings.add(substring)
    return valid_substrings
def find_kth_valid_string(test_cases):
    results = []
    for A, B, K in test_cases:
        # Generate valid substrings from A and B
        valid_substrings_A = generate_valid_substrings(A)
        valid_substrings_B = generate_valid_substrings(B)
        common_valid_substrings = valid_substrings_A & valid_substrings_B
        valid_common_substrings = sorted(common_valid_substrings)
        if len(valid_common_substrings) >= K:
            results.append(valid_common_substrings[K - 1])
        else:
            results.append("-1")
    return results
T = int(input())
test_cases = []
for _ in range(T):
    A, B, K = map(str, input().split())
    K = int(K)  # Convert K to integer
    test_cases.append((A, B, K))
results = find_kth_valid_string(test_cases)
for result in results:
    print(result)