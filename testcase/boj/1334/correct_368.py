s = [c for c in str(int(input())+1)]
N = len(s)

while True:
    is_pali = True
    for i in range(N//2):
        if s[i] != s[N-i-1]:
            is_pali = False
            break
    if is_pali:
        print(''.join(s))
        break
    for i in range(N//2):
        c = s[i]
        ct = s[N-i-1]
        if c == ct:
            continue
        if c > ct:
            s[N-i-1] = c
            continue
        s[N-i-1] = c
        t = N-i-2
        while t >= i:
            if s[t] != '9':
                s[t] = chr(ord(s[t])+1)
                break
            s[t] = '0'
            t -= 1
