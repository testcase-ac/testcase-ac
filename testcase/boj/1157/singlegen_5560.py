# Generate a 1,000,000‐character string with a perfect tie between 'A' and 'B'
# to force the output to be '?' in the worst case.
import sys

n = 10**6
half = n // 2
s = 'A' * half + 'B' * (n - half)
sys.stdout.write(s)
