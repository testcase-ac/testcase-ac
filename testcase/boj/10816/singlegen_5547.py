# Generate a maximum-size test for the "숫자 카드" problem:
# N = 500_000 cards, values in the allowed range [-10⁷,10⁷].
# M = 500_000 queries, re-using the same range so every query hits exactly one card.
N = 500_000
M = 500_000
print(N)
# produce N distinct card values from -10_000_000 up to -10_000_000+N-1
print(*range(-10_000_000, -10_000_000 + N))
print(M)
# query the same sequence, so each query count = 1
print(*range(-10_000_000, -10_000_000 + M))
