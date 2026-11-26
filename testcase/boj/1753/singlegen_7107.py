# Head insertion reverses these parallel edges, so all ten weights improve
# the distance to each vertex. This stresses heap capacity and queue updates.

def main():
    N = 20000
    M = 10 * (N - 1)
    print(f"{N} {M}")
    print(1)
    for v in range(2, N + 1):
        for w in range(1, 11):
            print(f"1 {v} {w}")

if __name__ == "__main__":
    main()
