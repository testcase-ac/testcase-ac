import sys

def main():
    # Construct a case with multiple testcases so that the global keyIdx (not reset between tests)
    # exceeds the isDeleted array bounds (size 1_000_001). This should cause out-of-bounds access.
    # Test 1: 1,000,000 inserts (keys 0..999,999)
    # Test 2: 200,000 inserts with strictly increasing values so the top has the last key (1,199,999)
    # The wrong code will access isDeleted[1_199_999] during final pop, which is OOB.
    print(2)
    # Test case 1
    print(1000000)
    sys.stdout.write(("I 0\n") * 1000000)
    # Test case 2
    print(200000)
    for i in range(1, 200001):
        sys.stdout.write(f"I {i}\n")

if __name__ == "__main__":
    main()
