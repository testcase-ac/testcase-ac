# This generator triggers 32-bit integer overflow in the wrong solution's final output formula.
# We build a star tree with root labeled n, and ask for k=2 so that for x=1 the LCA becomes n.
# With n >= 46342, (lca-1)*n overflows 32-bit int in the wrong code.

def main():
    n = 46342
    q = 1
    parents = [n] * (n - 1) + [0]  # nodes 1..n-1 have parent n; node n is root
    print(n, q)
    print(' '.join(map(str, parents)))
    # Choose k=2 so x=1 and the second smallest in x=1 block has LCA = n and y=2
    print(2)

if __name__ == '__main__':
    main()
