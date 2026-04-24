def go(a, b, c):
    if c == 1:
        return f'range({a},{b})'
    else:
        return f'range({a},{b},{c})'

def solve(rng):
    if len(rng) == 0:
        return 'range(-1)'
    elif len(rng) == 1:
        s = rng.start
        e = -1 if s != -1 else -10
        fst = e - s
        if e > s:
            d = [10**i for i in range(10) if 10**i >= fst][0]
        else:
            d = [-(10**i) for i in range(10) if -(10**i) <= fst][0]
        return go(s, e, d)
    else:
        s, e, d = rng.start, rng.stop, rng.step
        if d > 0:
            e = s + (e - s - 1) // d * d + 1
            tmp = range(e, e + d)
        else:
            e = s - (s - e - 1) // (-d) * (-d) - 1
            tmp = range(e, e + d, -1)
        ls = [0] + [10**i for i in range(10)] + [-(10**i) for i in range(10)]
        ls.sort(key=str)
        for i in ls:
            if i in tmp:
                return go(s, i, d)
        return go(s, min(tmp[0], tmp[-1], key=str), d)

print(solve(eval(input())))
