# Generates a skewed (left-chain) binary tree case that causes deep recursion.
# Wrong solution lacks recursionlimit adjustment, so it will hit RecursionError for n > ~1000.

def main():
    n = 2000  # Deep enough to exceed Python's default recursion limit
    inorder = list(range(1, n + 1))      # Inorder of left-skewed tree
    postorder = list(range(1, n + 1))    # Postorder of left-skewed tree

    print(n)
    print(" ".join(map(str, inorder)))
    print(" ".join(map(str, postorder)))

if __name__ == "__main__":
    main()
