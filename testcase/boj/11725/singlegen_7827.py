import sys

def main():
    n = 100000
    sys.stdout.write(str(n) + "\n")
    # Create a path tree 1-2-3-...-n, but list edges in reverse order to cause many requeues
    for i in range(n, 1, -1):
        sys.stdout.write(f"{i} {i-1}\n")

if __name__ == "__main__":
    main()
