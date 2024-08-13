def min_bubble_sort_passes(arr):
    n = len(arr)
    indexed_arr = [(val, idx) for idx, val in enumerate(arr)]
    
    indexed_arr.sort()
    
    max_displacement = 0
    for new_index, (value, original_index) in enumerate(indexed_arr):
        displacement = original_index - new_index
        if displacement > max_displacement:
            max_displacement = displacement
    
    return max_displacement + 1

import sys
input = sys.stdin.read
data = input().split()

N = int(data[0])
A = list(map(int, data[1:]))

print(min_bubble_sort_passes(A))