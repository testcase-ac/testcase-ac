import sys

def main():
    n = 7000
    out_lines = [str(n)]
    for i in range(n - 1):
        out_lines.append(f"{i} {i+1} 100")
    out_lines.append("0")
    sys.stdout.write("\n".join(out_lines))

if __name__ == "__main__":
    main()
