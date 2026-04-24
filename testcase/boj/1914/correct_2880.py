def main():
    from sys import stdin, stdout
    input = stdin.readline
    print = stdout.write
    def move(begin, finish, work, cnt):
        if cnt == 1:
            print('%d %d\n' % (begin, finish))
            return
        move(begin, work, finish, cnt-1)
        print('%d %d\n' % (begin, finish))
        move(work, finish, begin, cnt-1)

    n = int(input())
    print('%d\n' % (2**n-1))
    if n <= 20:
        move(1,3,2,n)
main()
