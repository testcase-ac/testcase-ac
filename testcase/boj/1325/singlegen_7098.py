# Generates a larger failing case where node 1 truly dominates,
# but the wrong solution ties 1 and 2 because it caps at 32.
def main():
    N = 80
    edges = []

    for i in range(2, 72):  # 2..71
        edges.append((i, 1))

    for i in range(31, 81):  # 31..80 (overlaps allowed)
        edges.append((i, 2))

    print(N, len(edges))
    for a, b in edges:
        print(a, b)

if __name__ == "__main__":
    main()
