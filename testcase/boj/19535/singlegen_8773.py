# Large star tree designed to cause the wrong solution's DFS (O(deg^2) on stars) to time out.
# N = 100000, center 1 connected to all others.
# Correct classification is G, but the wrong solution will likely TLE due to excessive DFS work.

def main():
    n = 100000
    print(n)
    for i in range(2, n+1):
        print(1, i)

if __name__ == "__main__":
    main()
