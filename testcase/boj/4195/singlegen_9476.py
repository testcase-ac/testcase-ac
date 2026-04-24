# Generates a single test case that breaks the wrong solution by exceeding its partial initialization limit (20001)
# It creates 10,001 friendship relations with all unique names (20,002 unique users),
# so the 20,001st ID is uninitialized in the wrong solution, causing incorrect output.

def make_name(i):
    letters = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
    if i == 0:
        return 'a'
    s = []
    while i > 0:
        s.append(letters[i % 52])
        i //= 52
    return ''.join(reversed(s))

def main():
    F = 10001
    print(1)
    print(F)
    for i in range(F):
        # Each pair introduces two new unique names
        print(make_name(2 * i), make_name(2 * i + 1))

if __name__ == "__main__":
    main()
