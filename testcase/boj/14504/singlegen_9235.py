# Generates a test case that breaks the wrong solution due to an off-by-one error
# in counting the right boundary when the query spans multiple buckets.
# Bucket size in the wrong solution is 316. We set N=317 so the array spans
# two buckets: indices 1..316 (first bucket) and 317 (second bucket).
# We then query the whole range [1,317]. The code incorrectly excludes index 317
# from counting, so it will miss the last element if it should be counted.

def main():
    N = 317
    # First 316 elements are small (1), last element is large (100)
    arr = [1]*316 + [100]
    M = 1
    # Query: count elements > 2 in [1, 317]. Correct answer is 1 (only the last element)
    print(N)
    print(" ".join(map(str, arr)))
    print(M)
    print("1 1 317 2")

if __name__ == "__main__":
    main()
