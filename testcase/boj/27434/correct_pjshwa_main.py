import sys

if hasattr(sys, "set_int_max_str_digits"):
    sys.set_int_max_str_digits(0)

n = int(input())
ans = 1
for i in range(n): ans *= (i + 1)
print(ans)
