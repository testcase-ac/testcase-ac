import sys

def main():
    n = 65537
    k = 65536
    out_lines = [f"{n} {k}\n"]
    out_lines += ["AA\n"] * n
    sys.stdout.write(''.join(out_lines))

if __name__ == "__main__":
    main()
