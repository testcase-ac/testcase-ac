import sys

def main():
    n = 100000
    out_lines = [str(n)]
    # Create a path (chain) tree: 1-2-3-...-n with weight 1
    # This will cause extremely deep recursion and O(n^2) DFS runs in the wrong solution
    out_lines.append("1 2 1 -1")
    for i in range(2, n):
        out_lines.append(f"{i} {i-1} 1 {i+1} 1 -1")
    out_lines.append(f"{n} {n-1} 1 -1")
    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    main()
