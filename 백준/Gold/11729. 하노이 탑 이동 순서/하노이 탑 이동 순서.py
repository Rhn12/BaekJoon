def hanoi(n, start, end, auxiliary, moves):
    if n == 1:
        moves.append((start, end))
        return
    hanoi(n-1, start, auxiliary, end, moves)
    moves.append((start, end))
    hanoi(n-1, auxiliary, end, start, moves)

def main():
    n = int(input().strip())
    moves = []
    hanoi(n, 1, 3, 2, moves)
    print(len(moves))
    for move in moves:
        print(move[0], move[1])

if __name__ == "__main__":
    main()