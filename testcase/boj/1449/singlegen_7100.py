def gen():
    # N = 2 leaks, tape length L chosen so one tape is enough in theory.
    # Wrong algorithm will count 2 because it artificially limits coverage to positions < 1000.
    print("2 21")          # N=2, L=21
    print("980 1000")      # leak positions
if __name__ == "__main__":
    gen()
