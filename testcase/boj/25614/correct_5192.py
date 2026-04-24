def main():
    import sys
    input = sys.stdin.readline
    print = sys.stdout.write
    n, m = map(int, input().split())
    arr = [0] + list(map(int, input().split()))
    
    nxt = [0 for i in range(n+1)]
    for i in range(1, n+1):
        nxt[arr[i]] = i
    seen = [False for i in range(n+1)]
    ans = [0 for i in range(n+1)]
    memo = {}
    for i in range(n):
        if seen[i]:
            continue
        ls = [i]
        cur = i
        while True:
            seen[cur] = True
            cur = nxt[cur]
            if cur == i:
                break
            ls.append(cur)
        if len(ls) in memo:
            mv = memo[len(ls)]
        else:
            mv = m % len(ls)
            memo[len(ls)] = mv
        j = (len(ls) - mv) % len(ls)
        for i in range(len(ls)):
            ans[ls[i]] = ls[j]
            j += 1
            if j == len(ls):
                j = 0
        
    print(' '.join(str(i) for i in ans[1:]))

if __name__ == '__main__':
    main()
