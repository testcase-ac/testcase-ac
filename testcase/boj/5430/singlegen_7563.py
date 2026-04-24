import sys

def main():
    T = 1
    n = 100000
    p = 'R' * 100000
    print(T)
    print(p)
    print(n)
    sys.stdout.write('[')
    for i in range(n):
        if i:
            sys.stdout.write(',')
        sys.stdout.write('1')
    sys.stdout.write(']\n')

if __name__ == "__main__":
    main()
