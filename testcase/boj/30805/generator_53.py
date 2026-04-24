import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants
MIN_N = 1
MAX_N = 10
MIN_VAL = 1
MAX_VAL = 10

def generate_random_sequence(n):
    """Generate a random sequence of length n with values between MIN_VAL and MAX_VAL."""
    return [random.randint(MIN_VAL, MAX_VAL) for _ in range(n)]

def generate_fully_overlapping_sequences(n):
    """Generate two identical sequences of length n."""
    seq = generate_random_sequence(n)
    return seq, seq

def generate_no_common_elements(n, m):
    """Generate two sequences with no common elements."""
    seq_a = [random.randint(MIN_VAL, MAX_VAL // 2) for _ in range(n)]
    seq_b = [random.randint((MAX_VAL // 2) + 1, MAX_VAL) for _ in range(m)]
    return seq_a, seq_b

def generate_partial_overlap(n, m):
    """Generate two sequences with partial overlap."""
    common_length = random.randint(1, min(n, m))
    common_sequence = generate_random_sequence(common_length)
    
    seq_a = generate_random_sequence(n - common_length) + common_sequence
    seq_b = generate_random_sequence(m - common_length) + common_sequence
    
    random.shuffle(seq_a)
    random.shuffle(seq_b)
    
    return seq_a, seq_b

def generate_increasing_sequences(n, m):
    """Generate two strictly increasing sequences."""
    seq_a = sorted(generate_random_sequence(n))
    seq_b = sorted(generate_random_sequence(m))
    return seq_a, seq_b

def generate_test_case():
    """Generate a random test case by selecting one of the predefined test case types."""
    case_type = random.choice(["random", "fully_overlapping", "no_common", "partial_overlap", "increasing"])
    
    n = random.randint(MIN_N, MAX_N)
    m = random.randint(MIN_N, MAX_N)
    
    if case_type == "random":
        seq_a = generate_random_sequence(n)
        seq_b = generate_random_sequence(m)
    elif case_type == "fully_overlapping":
        seq_a, seq_b = generate_fully_overlapping_sequences(n)
    elif case_type == "no_common":
        seq_a, seq_b = generate_no_common_elements(n, m)
    elif case_type == "partial_overlap":
        seq_a, seq_b = generate_partial_overlap(n, m)
    elif case_type == "increasing":
        seq_a, seq_b = generate_increasing_sequences(n, m)
    
    return n, seq_a, m, seq_b

def print_test_case(n, seq_a, m, seq_b):
    """Print the test case in the required format."""
    print(len(seq_a))
    print(" ".join(map(str, seq_a)))
    print(len(seq_b))
    print(" ".join(map(str, seq_b)))

# Example usage: generate and print a random test case
n, seq_a, m, seq_b = generate_test_case()
print_test_case(n, seq_a, m, seq_b)
