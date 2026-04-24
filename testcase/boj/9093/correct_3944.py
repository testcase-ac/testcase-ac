def main():
    from sys import stdin, stdout
    input = stdin.readline
    print = stdout.write
    n = int(input())
    for i in range(n):
        print(' '.join(s[::-1] for s in input().split()))
        print('\n')
main()
