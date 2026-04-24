import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

def generate_test_case():
    # Step 1: Generate N (exit position) and M (number of sticky plants)
    N = random.randint(3, 10)  # Keeping N small for easy verification
    M = random.randint(0, N-1)  # M must be less than N

    # Step 2: Generate M sticky plants
    sticky_plants = []
    x_coords = set()

    for _ in range(M):
        c = random.choice([0, 1])  # 0 for below, 1 for above
        x = random.randint(1, N-1)  # x should be between 1 and N-1 (not 0 and not N)
        
        while x in x_coords:
            x = random.randint(1, N-1)  # Ensure x is unique
        
        x_coords.add(x)
        
        h = random.randint(-10, 10)  # Small range for easier verification
        
        sticky_plants.append((c, x, h))
    
    # Output the generated test case
    print(f"{N} {M}")
    for plant in sticky_plants:
        print(f"{plant[0]} {plant[1]} {plant[2]}")

# Run the test case generator
generate_test_case()
