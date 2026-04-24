import sys

def main():
    n = 100000
    # 1 test case
    print(1)
    # Command string: 100000 D operations to force O(n^2) behavior in the wrong solution
    print('D' * n)
    # Array size
    print(n)
    # Array contents: n numbers within [1,100]
    w = sys.stdout.write
    w('[')
    for i in range(n):
        if i:
            w(',')
        w('1')
    w(']')

if __name__ == '__main__':
    main()
