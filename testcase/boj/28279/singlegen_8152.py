# Generates a heavy deque test causing TLE for list-based front inserts/pop(0)
# Commands: many front inserts (O(n) each) then a single size query
import sys

def main():
    inserts = 200000  # large enough to make list.insert(0, x) quadratic and timeout
    sys.stdout.write(str(inserts + 1) + "\n")
    # Perform many front inserts; minimal output commands to avoid IO bottleneck
    for _ in range(inserts):
        sys.stdout.write("1 1\n")
    # One output command to satisfy problem requirement
    sys.stdout.write("5\n")

if __name__ == "__main__":
    main()
