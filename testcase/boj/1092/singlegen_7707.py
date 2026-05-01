import sys

def main():
    n = 50
    cranes = [1] * 49 + [1000000]
    m = 10000
    boxes = [1000000] * m

    # Output
    print(n)
    print(' '.join(map(str, cranes)))
    print(m)
    # Large line but within limits
    print(' '.join(map(str, boxes)))

if __name__ == "__main__":
    main()
