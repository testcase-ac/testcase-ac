import sys

N = 100000

s = ["H"] * N
s[N // 2] = "G"
sys.stdout.write(f"{N}\n{''.join(s)}\n")
