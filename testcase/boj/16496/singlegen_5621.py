import random

def generate_max_test():
    random.seed(0)
    N = 1000
    # Build 100 copies of each 9-digit number '9'*9, '8'*9, ..., '1'*9, plus 100 zeros
    nums = []
    for d in range(9, 0, -1):
        s = str(d) * 9       # e.g. '999999999', '888888888', ...
        nums += [s] * 100
    nums += ['0'] * 100      # 100 zeros
    # Shuffle to avoid already-sorted order
    random.shuffle(nums)
    # Output
    print(N)
    print(' '.join(nums))

if __name__ == "__main__":
    generate_max_test()
