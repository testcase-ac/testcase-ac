import sys
input=sys.stdin.readline
n=int(input())
C2='BaekjoonOnlineJudge!'
C3='QbccWQx8WorvKRjiG+Qq41GFbA4M72UxtzueKz11iKpRiddvEXnjm4u9VfHKdfZl9mmfjrlNBBEAAAAAAAAAAHpfA6Vyzyu18GET3vZx3UNDJmNNhaS56lutf//RKYyB7CBKHZLezb0mguYhI65KFoyHytHtwpZPKIy6WdBaw13TclYVfN/lq2L/byJDm99y//////////+0S7HSpdYpg04VcG2uKMqX4mR4Xa5h1iSzQOuqhKze3rWGAEFp/R4gwRV4OPa7JP3XSrCaCZXQNLo1pm5eIWVtbnfCVulfJ8gvkHaWs/eDR+L331ybWsFbYhLzgk8+a/DR9w54RXu8AQ'
C5='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'
C7='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'
I6=[13,17,19,28,31,37,39,46,64,71,73,79,82,91,93,97]
D=[-1,-1,0,1,1,1,0,-1]
D2=[0,1,1,1,0,-1,-1,-1]
# ////////////////////////////////////
def b64d(s):
    b=[]
    for ch in s.encode():
        if 65<=ch<=90:v=ch-65
        elif 97<=ch<=122:v=ch-71
        elif 48<=ch<=57:v=ch+4
        elif ch==43:v=62
        else:v=63
        for j in range(5,-1,-1):
            b.append((v>>j)&1)
    return b

def b64e(bits):
    out=[]
    m=len(bits)//6*6
    for i in range(0,m,6):
        v=0
        for j in range(6):
            v|=bits[i+j]<<(5-j)
        if v<26:out.append(chr(v+65))
        elif v<52:out.append(chr(v+71))
        elif v<62:out.append(chr(v-4))
        elif v==62:out.append('+')
        else:out.append('/')
    return ''.join(out)

def o0():
    print('BOJ 20000')

def o1():
    w=sys.stdout.write
    w('#include <cstdio>\nint main(){\n    int N;\n    scanf("%d",&N);\n    ')
    for i in range(1,20001):
        w(f'if(N=={i}){{\n        puts("{i*4}");\n    }}\n')
        if i<20000:
            w('    else ')
        else:
            w('    else{\n        puts("Still working on it...");\n    }\n    return 0;\n}\n')

def o2():
    w=sys.stdout.write
    for i in range(1,1048576):
        t=0
        j=i
        while j%2==0:
            t+=1
            j//=2
        w(C2[t])
    w('\n')

def o3():
    bits=b64d(C3)
    board=[bytearray(b' '*2400) for _ in range(2400)]
    sys.setrecursionlimit(10000)
    def n31(s,h):
        if h==1:
            if bits[s]:
                board[1023][s]=47
            if bits[s+1]:
                board[1023][s+1]=92
            return
        l=r=0
        m=s+h
        for i in range(s,m):
            if bits[i]:
                l=1
            if bits[h+i]:
                r=1
        if l:
            for i in range(h,h//2,-1):
                board[1024-i][s+i-1]=47
            n31(s,h//2)
        if r:
            for i in range(h,h//2,-1):
                board[1024-i][s+2*h-i]=92
            n31(m,h//2)
    n31(0,1024)
    w=sys.stdout.buffer.write
    for i in range(1024):
        w(board[i][:1025+i]+b'\n')

def o4():
    pr=[]
    for i in range(2,1024):
        t=1
        j=2
        while j*j<=i:
            if i%j==0:
                t=0
            j+=1
        if t:
            pr.append(i)
    w=sys.stdout.write
    for i in range(1000):
        row=[]
        for j in range(i+1):
            x=i^j
            t=0
            for p in pr:
                if x==p:
                    t=1
                    break
            row.append('#' if t else '.')
        w(''.join(row)+'\n')

def o5():
    sys.stdout.write(C5*200+'\n')

def o6():
    chk=[0]*10
    pr=[0]*960
    w=sys.stdout.write
    def n61(m,n):
        if n==m:
            pp=0
            for i in range(1,n):
                for x in I6:
                    if pr[i-1]*10+pr[i]==x:
                        pp=1
                        for k in range(i-2,-1,-1):
                            if pr[k]*2==x%10+x//10:
                                pp=0
                        if pp:
                            break
                if pp:
                    break
            if pp:
                return
            pp=1
            for i in range(n):
                w(str(pr[i]))
                if pr[i]!=9-i:
                    pp=0
            w('\n' if pp and n==9 else ' ')
            return
        for i in range(1,10):
            if not chk[i]:
                chk[i]=1
                pr[n]=i
                n61(m,n+1)
                chk[i]=0
    for i in range(4,10):
        n61(i,0)

def o7():
    bits=b64d(C7)
    board=[bytearray(2400) for _ in range(2400)]
    sys.setrecursionlimit(10000)
    pp=0
    def n71(x,y,l):
        nonlocal pp
        for i in range(l-3):
            board[x+i][y]=46
            board[x-i][y]=46
            board[x][y+i]=46
            board[x][y-i]=46
        if bits[pp]:
            for i in range(1,5):
                board[x-l+4][y-i]=46
        else:
            for i in range(1,5):
                board[x-i][y-l+4]=46
        pp+=1
        if bits[pp]:
            for i in range(1,5):
                board[x-i][y+l-4]=46
        else:
            for i in range(1,5):
                board[x-l+4][y+i]=46
        pp+=1
        if bits[pp]:
            for i in range(1,5):
                board[x+l-4][y+i]=46
        else:
            for i in range(1,5):
                board[x+i][y+l-4]=46
        pp+=1
        if bits[pp]:
            for i in range(1,5):
                board[x+i][y-l+4]=46
        else:
            for i in range(1,5):
                board[x+l-4][y-i]=46
        pp+=1
        if l==8:
            return
        l//=2
        n71(x-l,y-l,l)
        n71(x-l,y+l,l)
        n71(x+l,y+l,l)
        n71(x+l,y-l,l)
    n71(512,512,512)
    w=sys.stdout.buffer.write
    for i in range(3,1022):
        row=bytearray(1019)
        t=0
        for j in range(3,1022):
            if board[i][j]==46:
                row[t]=46
            else:
                ok=1
                for k in range(8):
                    if board[i+D[k]][j+D2[k]]==46:
                        ok=0
                        break
                row[t]=46 if ok else 35
            t+=1
        w(row+b'\n')

def o8():
    bits=[0]*4782969
    sys.setrecursionlimit(1000000)
    def n81(s,n):
        if n==1:
            bits[s]=1
            return
        n//=3
        for p in (0,1,2,2187,2189,4374,4375,4376):
            n81(s+n*p,n)
    n81(0,2187)
    sys.stdout.write(b64e(bits)+'\n')

def o9():
    m=1695327975
    w=sys.stdout.write
    for i in range(100000):
        v=((376739550*i)%m*i%m*i%m*i%m+(28540875*i)%m*i%m*i%m+(565524465*i)%m*i%m+(855292706*i)%m+20000)%m
        w(str(v))
        w(',' if i<99999 else '\n')

[o0,o1,o2,o3,o4,o5,o6,o7,o8,o9][n]()
