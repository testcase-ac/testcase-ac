import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants
MAX_T = 2  # Maximum number of test cases
MIN_M = 1  # Minimum width of the field
MAX_M = 10  # Maximum width of the field
MIN_N = 1  # Minimum height of the field
MAX_N = 10  # Maximum height of the field
MIN_K = 1  # Minimum number of cabbages
MAX_K = 16  # Maximum number of cabbages to keep the output small

def generate_random_test_case():
    """Generates a test case with random cabbage positions."""
    M = random.randint(MIN_M, MAX_M)
    N = random.randint(MIN_N, MAX_N)
    total_positions = M * N
    K = random.randint(MIN_K, min(total_positions, MAX_K))
    possible_positions = [(x, y) for x in range(M) for y in range(N)]
    positions = set(random.sample(possible_positions, K))
    test_case = f"{M} {N} {K}\n"
    for x, y in positions:
        test_case += f"{x} {y}\n"
    return test_case.strip()

def generate_single_connected_component_case():
    """Generates a test case where all cabbages form a single connected component."""
    M = random.randint(MIN_M, MAX_M)
    N = random.randint(MIN_N, MAX_N)
    total_positions = M * N
    x0, y0 = random.randint(0, M - 1), random.randint(0, N - 1)
    positions = {(x0, y0)}
    frontier = [(x0, y0)]
    K = random.randint(MIN_K, min(total_positions, MAX_K))
    while len(positions) < K and frontier:
        x, y = frontier.pop(0)
        neighbors = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        random.shuffle(neighbors)
        for dx, dy in neighbors:
            nx, ny = x + dx, y + dy
            if 0 <= nx < M and 0 <= ny < N and (nx, ny) not in positions:
                positions.add((nx, ny))
                frontier.append((nx, ny))
                if len(positions) >= K:
                    break
        if len(positions) >= K:
            break
    test_case = f"{M} {N} {len(positions)}\n"
    for x, y in positions:
        test_case += f"{x} {y}\n"
    return test_case.strip()

def generate_disconnected_cabbages_case():
    """Generates a test case where no two cabbages are adjacent."""
    M = random.randint(MIN_M + 1, MAX_M)
    N = random.randint(MIN_N + 1, MAX_N)
    possible_positions = [(x, y) for x in range(0, M, 2) for y in range(0, N, 2)]
    K = random.randint(MIN_K, min(len(possible_positions), MAX_K))
    positions = set(random.sample(possible_positions, K))
    test_case = f"{M} {N} {len(positions)}\n"
    for x, y in positions:
        test_case += f"{x} {y}\n"
    return test_case.strip()

def generate_max_components_case():
    """Generates a test case with the maximum number of connected components."""
    M = random.randint(MIN_M + 2, MAX_M)
    N = random.randint(MIN_N + 2, MAX_N)
    possible_positions = [(x, y) for x in range(0, M, 2) for y in range(0, N, 2)]
    positions = set()
    for pos in possible_positions:
        positions.add(pos)
        if len(positions) >= MAX_K:
            break
    test_case = f"{M} {N} {len(positions)}\n"
    for x, y in positions:
        test_case += f"{x} {y}\n"
    return test_case.strip()

def main():
    T = random.randint(1, MAX_T)
    print(T)
    for _ in range(T):
        test_case_type = random.choice(['random', 'connected', 'disconnected', 'max_components'])
        if test_case_type == 'random':
            print(generate_random_test_case())
        elif test_case_type == 'connected':
            print(generate_single_connected_component_case())
        elif test_case_type == 'disconnected':
            print(generate_disconnected_cabbages_case())
        elif test_case_type == 'max_components':
            print(generate_max_components_case())

if __name__ == "__main__":
    main()
