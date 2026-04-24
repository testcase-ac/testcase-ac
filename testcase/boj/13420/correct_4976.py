for i in range(int(input())):
    s = input().split('=')
    print('correct' if eval(s[0]) == eval(s[1]) else 'wrong answer')
