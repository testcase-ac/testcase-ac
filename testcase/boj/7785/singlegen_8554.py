# Generates a worst-case test for the given C solution by forcing extreme hash collisions.
# All names will have the same ASCII sum (thus same hash bucket), leading to O(n^2) insert time.
# We generate about 150,000 unique 5-letter names whose ASCII sum is constant.

import sys
from itertools import combinations

def allowed_codes():
    # ASCII codes for A-Z and a-z
    return list(range(65, 91)) + list(range(97, 123))

CODES = set(allowed_codes())

# Build ordered pairs (u, v) of letters such that u + v == const_sum
# Returns list of 2-char strings

def build_pairs(const_sum):
    pairs = []
    for u in CODES:
        v = const_sum - u
        if v in CODES:
            pairs.append((chr(u), chr(v)))
    return pairs

# Target: keep total ASCII sum constant for all 5-letter names
# We'll set: total_sum = pair1_sum + pair2_sum + ord('A')
# Choose total_sum so that both pair sums have many valid pairs.
# Let pair1_sum + pair2_sum = 374 (near center), and c5 = 'A' (65), so total_sum = 439.

PAIR_TOTAL = 374
C5_CHAR = 'A'

# Choose two good pair sums whose counts are large.
PAIR_SUMS = [187, 186]  # 187 has 52 ordered pairs, 186 has 50; 187+187 and 186+188 both equal 374

# Precompute pairs for all needed sums (including complementary sums)
PAIRS_CACHE = {}
for s in set(PAIR_SUMS + [PAIR_TOTAL - x for x in PAIR_SUMS]):
    PAIRS_CACHE[s] = build_pairs(s)

# Target number of names. 150k should be plenty to TLE the wrong solution via O(n^2) hashing bucket behavior.
TARGET = 150000
names = []
seen = set()

positions_all = [0, 1, 2, 3, 4]

for s1 in PAIR_SUMS:
    s2 = PAIR_TOTAL - s1
    pairs1 = PAIRS_CACHE[s1]
    pairs2 = PAIRS_CACHE[s2]

    # For each position of the fixed character C5_CHAR
    for c5_pos in positions_all:
        other_pos = [p for p in positions_all if p != c5_pos]
        # Choose positions for the first pair among the 4 remaining positions
        for pos_pair in combinations(other_pos, 2):
            pos_pair = list(pos_pair)
            rem = [p for p in other_pos if p not in pos_pair]
            rem.sort()
            # Fill pair2 in remaining positions in order of pair characters
            for a, b in pairs1:
                for c, d in pairs2:
                    arr = [''] * 5
                    arr[c5_pos] = C5_CHAR
                    arr[pos_pair[0]] = a
                    arr[pos_pair[1]] = b
                    arr[rem[0]] = c
                    arr[rem[1]] = d
                    name = ''.join(arr)
                    if name not in seen:
                        seen.add(name)
                        names.append(name)
                        if len(names) >= TARGET:
                            break
                if len(names) >= TARGET:
                    break
            if len(names) >= TARGET:
                break
        if len(names) >= TARGET:
            break
    if len(names) >= TARGET:
        break

# Fallback: if for any reason we didn't reach TARGET (unlikely), fill more using a simple scheme
if len(names) < TARGET:
    # As a simple extension, vary the fixed character position and reuse more pair sums around the center
    for s1 in range(170, 205):
        s2 = PAIR_TOTAL - s1
        if s1 not in PAIRS_CACHE:
            PAIRS_CACHE[s1] = build_pairs(s1)
        if s2 not in PAIRS_CACHE:
            PAIRS_CACHE[s2] = build_pairs(s2)
        pairs1 = PAIRS_CACHE[s1]
        pairs2 = PAIRS_CACHE[s2]
        if not pairs1 or not pairs2:
            continue
        for c5_pos in positions_all:
            other_pos = [p for p in positions_all if p != c5_pos]
            for pos_pair in combinations(other_pos, 2):
                pos_pair = list(pos_pair)
                rem = [p for p in other_pos if p not in pos_pair]
                rem.sort()
                for a, b in pairs1:
                    for c, d in pairs2:
                        arr = [''] * 5
                        arr[c5_pos] = C5_CHAR
                        arr[pos_pair[0]] = a
                        arr[pos_pair[1]] = b
                        arr[rem[0]] = c
                        arr[rem[1]] = d
                        name = ''.join(arr)
                        if name not in seen:
                            seen.add(name)
                            names.append(name)
                            if len(names) >= TARGET:
                                break
                    if len(names) >= TARGET:
                        break
                if len(names) >= TARGET:
                    break
            if len(names) >= TARGET:
                break
        if len(names) >= TARGET:
            break

# Output the test case: n lines of "name enter"
print(len(names))
for nm in names:
    print(nm + " enter")
