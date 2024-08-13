def is_possible_count(cnt_of_people, averages):
    for avg in averages:
        left = 0
        right = 10 * cnt_of_people
        is_possible = False
        while left <= right:
            sum_of_score = (left + right) // 2
            current_avg = (sum_of_score * 1000) // cnt_of_people
            if current_avg == avg:
                if current_avg > 10 * 1000:
                    continue
                is_possible = True
                break
            elif current_avg > avg:
                right = sum_of_score - 1
            else:
                left = sum_of_score + 1
        if not is_possible:
            return False
    return True

def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    n = int(data[0])
    averages = []
    for i in range(1, n+1):
        parts = data[i].split('.')
        combined = parts[0] + parts[1]
        averages.append(int(combined))
    for cnt_of_people in range(1, 1001):
        if is_possible_count(cnt_of_people, averages):
            print(cnt_of_people)
            break
if __name__ == "__main__":
    main()