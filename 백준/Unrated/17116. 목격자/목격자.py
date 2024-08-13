import sys

def main():
    c = sys.stdin.read().strip()
    if len(c) > 0:
        c = ord(c[0])
        
        if c == 75 or c == 76:
            print('BABA IS WIN')
        elif c == 66 or c == 84:
            print('BABA IS NOT WIN')

if __name__ == "__main__":
    main()