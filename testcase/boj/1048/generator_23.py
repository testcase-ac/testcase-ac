import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants for bounds
N_MIN = 1
N_MAX = 10
M_MIN = 1
M_MAX = 10
L_MIN = 1
L_MAX = 5
WORD_LEN_MIN = 1
WORD_LEN_MAX = 10
ALPHABET = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

def generate_random_word(length, letters):
    return ''.join(random.choice(letters) for _ in range(length))

def generate_random_board(N, M, letters):
    return [''.join(random.choice(letters) for _ in range(M)) for _ in range(N)]

def testcase_type_small_random():
    # Small board with random letters, short word
    N = random.randint(N_MIN, N_MAX)
    M = random.randint(M_MIN, M_MAX)
    L = random.randint(L_MIN, L_MAX)
    letters = ALPHABET[:L]
    board = generate_random_board(N, M, letters)
    word_length = random.randint(WORD_LEN_MIN, WORD_LEN_MAX)
    word = generate_random_word(word_length, letters)
    return N, M, L, word, board

def testcase_type_uniform_letters():
    # Board with all same letters, word is repeated letter
    N = random.randint(N_MIN, N_MAX)
    M = random.randint(M_MIN, M_MAX)
    L = 1  # Only one letter
    letters = ALPHABET[:L]
    board = [letters[0] * M for _ in range(N)]
    word_length = random.randint(WORD_LEN_MIN, WORD_LEN_MAX)
    word = letters[0] * word_length
    return N, M, L, word, board

def testcase_type_max_letters():
    # Board uses maximum L letters
    N = random.randint(N_MIN, N_MAX)
    M = random.randint(M_MIN, M_MAX)
    L = L_MAX
    letters = ALPHABET[:L]
    board = generate_random_board(N, M, letters)
    word_length = random.randint(WORD_LEN_MIN, WORD_LEN_MAX)
    word = generate_random_word(word_length, letters)
    return N, M, L, word, board

def testcase_type_long_word():
    # Word is longer than board dimensions
    N = random.randint(N_MIN, N_MAX)
    M = random.randint(M_MIN, M_MAX)
    L = random.randint(L_MIN, L_MAX)
    letters = ALPHABET[:L]
    board = generate_random_board(N, M, letters)
    word_length = max(N * M + random.randint(1, 5), WORD_LEN_MIN)
    word_length = min(word_length, WORD_LEN_MAX)
    word = generate_random_word(word_length, letters)
    return N, M, L, word, board

def testcase_type_edge_case():
    # Edge case: N=1, M=1, word length=1
    N = N_MIN
    M = M_MIN
    L = random.randint(L_MIN, L_MAX)
    letters = ALPHABET[:L]
    board = [random.choice(letters)]
    word = board[0]
    return N, M, L, word, board

def generate_testcase():
    testcase_generators = [
        testcase_type_small_random,
        testcase_type_uniform_letters,
        testcase_type_max_letters,
        testcase_type_long_word,
        testcase_type_edge_case
    ]
    # Randomly select a test case type
    testcase_function = random.choice(testcase_generators)
    N, M, L, word, board = testcase_function()

    # Output the test case
    print(f"{N} {M} {L}")
    print(word)
    for row in board:
        print(row)

# Generate the test case
generate_testcase()
