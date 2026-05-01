# Generate a single maximal test‐case:
# T = 1, n = 30, and each of the 30 items is in its own unique category.
cats = [chr(i) for i in range(ord('a'), ord('z')+1)] + ['aa','ab','ac','ad']
print(1)       # one test case
print(30)      # maximum n
for c in cats:
    # item name and category name are the same (both lowercase), no repeats
    print(c, c)
