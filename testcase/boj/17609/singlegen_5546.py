# Generate a maximal test for the palindrome/pseudo-palindrome problem:
# T = 30 strings, each of length 100000, composed to cover:
#  - exact palindromes (answer 0)
#  - pseudo-palindromes by removing at start, end, or middle (answer 1)
#  - non-palindromes/non-pseudo-palindromes (answer 2)

import sys

def gen_pal(n):
    return 'a' * n

def gen_pseudo_begin(n):
    # remove first char makes all 'a's -> palindrome
    return 'b' + 'a' * (n - 1)

def gen_pseudo_end(n):
    # remove last char makes all 'a's -> palindrome
    return 'a' * (n - 1) + 'b'

def gen_pseudo_mid(n):
    # n is even; put a 'b' slightly off-center
    half = n // 2
    return 'a' * (half) + 'b' + 'a' * (half - 1)

def gen_non(n):
    # two mismatches at ends; no single removal fixes both
    return 'b' + 'a' * (n - 2) + 'c'

n = 100000
patterns = [gen_pal, gen_pseudo_begin, gen_pseudo_end, gen_pseudo_mid, gen_non]

T = 30
print(T)
for i in range(T):
    s = patterns[i % len(patterns)](n)
    print(s)
