# Generate a maximum-size test case for the prefix-matching problem.
# N = 20 000 (maximum), word length ≤ 100.
# The first two words share a common prefix of length 99 (max possible <100),
# and are distinct. The rest are all distinct 5-letter words.

N = 20000
print(N)
# Two words with maximal common prefix of length 99
print('a' * 99 + 'b')
print('a' * 99 + 'c')
# Generate the remaining N-2 distinct words (each length = 5, all lowercase)
for i in range(N - 2):
    # encode i in base-26 into 5 letters → ensures > 20 000 unique words
    c1 = chr(97 + (i // 26**4) % 26)
    c2 = chr(97 + (i // 26**3) % 26)
    c3 = chr(97 + (i // 26**2) % 26)
    c4 = chr(97 + (i // 26)     % 26)
    c5 = chr(97 + (i)           % 26)
    print(c1 + c2 + c3 + c4 + c5)
