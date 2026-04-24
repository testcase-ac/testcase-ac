import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

def generate_test_case():
    test_case_type = random.randint(1, 6)
    max_int = random.randint(1, 9)
    if test_case_type == 1:
        # Type 1: Random grid with random digits
        N = random.randint(1, 8)
        M = random.randint(1, 8)
        grid = [[str(random.randint(0, max_int)) for _ in range(M)] for _ in range(N)]
        
    elif test_case_type == 2:
        # Type 2: Grid with all digits the same
        N = random.randint(1, 8)
        M = random.randint(1, 8)
        digit = str(random.randint(0, max_int))
        grid = [[digit for _ in range(M)] for _ in range(N)]
        
    elif test_case_type == 3:
        # Type 3: Largest square in a corner
        N = random.randint(2, 8)
        M = random.randint(2, 8)
        grid = [[str(random.randint(0, max_int)) for _ in range(M)] for _ in range(N)]
        S = random.randint(2, min(N, M))
        digit = str(random.randint(0, max_int))
        # Top-left corner square
        grid[0][0] = digit
        grid[0][S-1] = digit
        grid[S-1][0] = digit
        grid[S-1][S-1] = digit
        
    elif test_case_type == 4:
        # Type 4: Grid with largest square size 1
        N = random.randint(1, 8)
        M = random.randint(1, 8)
        current_digit = 0
        grid = []
        for _ in range(N):
            row = []
            for _ in range(M):
                row.append(str(current_digit % 10))
                current_digit += 1
            grid.append(row)
            
    elif test_case_type == 5:
        # Type 5: Max N and M (10x10), random digits
        N = M = 8
        grid = [[str(random.randint(0, max_int)) for _ in range(M)] for _ in range(N)]
        
    elif test_case_type == 6:
        # Type 6: Specific pattern
        N = random.randint(5, 8)
        M = random.randint(5, 8)
        grid = []
        for i in range(N):
            row = []
            for j in range(M):
                if (i + j) % 2 == 0:
                    row.append('1')
                else:
                    row.append('0')
            grid.append(row)
    else:
        N = M = 1
        grid = [['0']]
        
    print(f"{N} {M}")
    for row in grid:
        print(''.join(row))

generate_test_case()
