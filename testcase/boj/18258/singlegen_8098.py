import sys

def main():
    # Craft a test to trigger TLE in the wrong solution due to using queue.Last() for "back" (O(n) each time).
    # We keep outputs moderate while ensuring huge total work: many "back" operations on a large queue.
    n_push = 100000
    n_back = 200000  # 200k back operations over a queue of size 100k => ~2e10 iterations in wrong solution
    N = n_push + n_back

    w = sys.stdout.write
    w(f"{N}\n")
    # Build a queue with many elements
    for _ in range(n_push):
        w("push 1\n")
    # Repeatedly query back (each is O(n) in the wrong solution)
    for _ in range(n_back):
        w("back\n")

if __name__ == "__main__":
    main()
