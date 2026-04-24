T = int(input())
for i in range(T):
    s = input()
    if s[len(s)//2-1] == s[len(s)//2]:
        print('Do-it')
    else:
        print('Do-it-Not')
