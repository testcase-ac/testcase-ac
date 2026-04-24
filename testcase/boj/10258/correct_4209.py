t = int(input())

def solve(inp, tgt):
    if not inp:
        return 0
    if inp[0] == tgt[0]:
        return solve(inp[1:], tgt[1:])
    if len(inp) == 1:
        return 1
    
    # 1XXXX -> 11000 -> 00000
    # 0XXXX -> 01000 -> 11000 -> 10000
    return solve(inp[1:], '1' + '0' * (len(inp) - 2)) + 2 ** (len(inp) - 1)
        

for i in range(t):
    s = input()
    print(solve(s, '0' * len(s)))
    
