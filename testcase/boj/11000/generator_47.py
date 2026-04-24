import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

def generate_test_case():
    # Constants for configuration
    N_MIN = 2       # Minimum number of lectures
    N_MAX = 5      # Maximum number of lectures
    S_MIN = 0       # Minimum start time
    S_MAX = 20     # Maximum start time
    D_MIN = 1       # Minimum duration
    D_MAX = 10      # Maximum duration

    random.seed()

    # Generate N, the number of lectures
    N = random.randint(N_MIN, N_MAX)
    intervals = []

    # Generate lectures in such a way that multiple lectures end before new ones start
    # This will create scenarios where classrooms should be reused
    end_time = S_MIN
    for _ in range(N):
        # Alternate between groups of overlapping lectures and non-overlapping ones
        if random.random() < 0.5:
            # Create a group of overlapping lectures
            group_size = random.randint(2, 3)
            start = end_time
            end = start + random.randint(D_MIN, D_MAX)
            for _ in range(group_size):
                # All lectures in this group start at the same time but have different end times
                duration = random.randint(D_MIN, D_MAX)
                intervals.append((start, start + duration))
        else:
            # Create a lecture that starts after previous lectures have ended
            start = end_time + random.randint(1, 5)
            duration = random.randint(D_MIN, D_MAX)
            end = start + duration
            intervals.append((start, end))
        end_time = max(end_time, end)

    # Shuffle intervals to randomize their order
    random.shuffle(intervals)

    # Output the test case
    print(len(intervals))
    for s, t in intervals:
        print(f"{s} {t}")

if __name__ == "__main__":
    generate_test_case()
