import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random
import string

def generate_test_case():
    # Constants for clarity and potential modification
    MIN_LENGTH = 5
    MAX_LENGTH = 10
    MIN_LETTERS = 2
    MAX_LETTERS = 5

    palindrome_possible = random.choice([True, False])

    if palindrome_possible:
        # Generate a name where a palindrome is possible
        N = random.randint(MIN_LENGTH, MAX_LENGTH)
        num_letters = random.randint(1, min(N, MAX_LETTERS))
        letters = random.sample(string.ascii_uppercase, num_letters)
        counts = [0] * num_letters

        if N % 2 == 0:
            # All counts should be even
            half_N = N // 2
            counts_half = random_partition(num_letters, half_N)
            counts = [c * 2 for c in counts_half]
        else:
            # One count is odd, others are even
            half_N = (N - 1) // 2
            counts_half = random_partition(num_letters, half_N)
            odd_idx = random.randint(0, num_letters - 1)
            counts = [c * 2 for c in counts_half]
            counts[odd_idx] += 1

        name_chars = []
        for i in range(num_letters):
            name_chars.extend([letters[i]] * counts[i])
        random.shuffle(name_chars)
        name = ''.join(name_chars)
        return name

    else:
        # Generate a name where a palindrome is impossible
        num_letters = random.randint(MIN_LETTERS, MAX_LETTERS)
        odd_letters = random.randint(2, num_letters)
        letters = random.sample(string.ascii_uppercase, num_letters)
        counts = []

        for i in range(num_letters):
            if i < odd_letters:
                counts.append(1)  # Assign odd counts
            else:
                counts.append(2)  # Assign even counts

        name_chars = []
        for i in range(num_letters):
            name_chars.extend([letters[i]] * counts[i])
        random.shuffle(name_chars)
        name = ''.join(name_chars)
        return name

def random_partition(K, N_counts):
    if N_counts == 0:
        return [0] * K
    counts = [random.random() for _ in range(K)]
    total = sum(counts)
    counts = [int(N_counts * (c / total)) for c in counts]
    remainder = N_counts - sum(counts)
    for i in range(remainder):
        counts[i % K] += 1
    return counts

# Generate and print the test case
test_case = generate_test_case()
print(test_case)
