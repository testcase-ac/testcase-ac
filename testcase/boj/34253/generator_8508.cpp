#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int N, K;

    if (mode == 0) {
        // Tiny random
        K = rnd.next(1, 5);
        N = rnd.next(1, 7);
    } else if (mode == 1) {
        // Mostly increasing chains
        K = rnd.next(2, 8);
        N = rnd.next(3, 12);
    } else if (mode == 2) {
        // Mostly decreasing chains
        K = rnd.next(2, 8);
        N = rnd.next(3, 12);
    } else if (mode == 3) {
        // Mixed random
        K = rnd.next(3, 10);
        N = rnd.next(8, 20);
    } else {
        // Many empty/full and extremes
        K = rnd.next(1, 8);
        N = rnd.next(6, 18);
    }

    vector<int> mask(N, 0);
    int fullMask = (1 << K) - 1;

    if (mode == 0) {
        // Tiny random masks
        for (int i = 0; i < N; ++i) {
            mask[i] = rnd.next(0, fullMask);
        }
    } else if (mode == 1) {
        // Increasing (by inclusion) with some duplicates
        int cur = rnd.next(0, fullMask);
        mask[0] = cur;
        for (int i = 1; i < N; ++i) {
            int choice = rnd.next(0, 2);
            if (choice == 0) {
                // Duplicate a previous mask
                int idx = rnd.next(0, i - 1);
                mask[i] = mask[idx];
            } else {
                // Try to add bits to make a superset of current
                int available = (~cur) & fullMask;
                if (available == 0) {
                    mask[i] = cur; // only duplicates possible
                } else {
                    int add = rnd.next(1, available); // ensure non-zero subset of available
                    add &= available;
                    if (add == 0) add = available & -available; // at least one bit
                    mask[i] = cur | add;
                    cur = mask[i];
                }
            }
        }
    } else if (mode == 2) {
        // Decreasing (by inclusion) with some duplicates
        int cur = rnd.next(0, fullMask);
        mask[0] = cur;
        for (int i = 1; i < N; ++i) {
            int choice = rnd.next(0, 2);
            if (choice == 0) {
                // Duplicate
                int idx = rnd.next(0, i - 1);
                mask[i] = mask[idx];
            } else {
                // Remove bits from current
                int have = cur;
                if (have == 0) {
                    mask[i] = cur; // only duplicates possible
                } else {
                    int rem = rnd.next(1, have); // non-zero subset to remove
                    rem &= have;
                    if (rem == 0) rem = have & -have;
                    mask[i] = cur & ~rem;
                    cur = mask[i];
                }
            }
        }
    } else if (mode == 3) {
        // Mixed random with subsets/supersets/duplicates
        for (int i = 0; i < N; ++i) {
            if (i == 0) {
                mask[i] = rnd.next(0, fullMask);
                continue;
            }
            int t = rnd.next(0, 4);
            if (t == 0) {
                // Pure random
                mask[i] = rnd.next(0, fullMask);
            } else if (t == 1) {
                // Duplicate some previous
                int idx = rnd.next(0, i - 1);
                mask[i] = mask[idx];
            } else if (t == 2) {
                // Subset of some previous
                int idx = rnd.next(0, i - 1);
                int base = mask[idx];
                int subMask = rnd.next(0, fullMask);
                mask[i] = base & subMask;
            } else if (t == 3) {
                // Superset of some previous
                int idx = rnd.next(0, i - 1);
                int base = mask[idx];
                int available = (~base) & fullMask;
                int add = rnd.next(0, fullMask);
                add &= available;
                mask[i] = base | add;
            } else {
                // Force empty sometimes
                mask[i] = 0;
            }
        }
    } else {
        // Mode 4: many empty/full and structured patterns
        for (int i = 0; i < N; ++i) {
            int r = i % 4;
            if (r == 0) {
                // Empty set
                mask[i] = 0;
            } else if (r == 1) {
                // Full set
                mask[i] = fullMask;
            } else if (r == 2) {
                // Random subset of full
                int sub = rnd.next(0, fullMask);
                mask[i] = sub;
            } else {
                // Subset of previous or superset of some earlier
                if (i == 0) {
                    mask[i] = rnd.next(0, fullMask);
                } else {
                    int choice = rnd.next(0, 1);
                    int idx = rnd.next(0, i - 1);
                    int base = mask[idx];
                    if (choice == 0) {
                        // Subset
                        int subMask = rnd.next(0, fullMask);
                        mask[i] = base & subMask;
                    } else {
                        // Superset
                        int available = (~base) & fullMask;
                        int add = rnd.next(0, fullMask);
                        add &= available;
                        mask[i] = base | add;
                    }
                }
            }
        }
    }

    // Determine which problems are WellKnown
    vector<bool> well(N, false);
    for (int i = 0; i < N; ++i) {
        bool w = false;
        for (int j = 0; j < i && !w; ++j) {
            // Problem j is a superset of i if all bits of i are included in j
            if ((mask[j] | mask[i]) == mask[j]) {
                w = true;
            }
        }
        well[i] = w;
    }

    // Encode S_i depending on z_i
    vector<string> S(N);
    for (int i = 0; i < N; ++i) {
        int zi;
        if (i == 0) zi = 0;
        else zi = well[i - 1] ? 0 : 1;

        string s(K, '0');
        if (zi == 0) {
            // Direct encoding
            for (int b = 0; b < K; ++b) {
                if (mask[i] & (1 << b)) {
                    s[b] = '1';
                }
            }
        } else {
            // Reversed encoding
            for (int b = 0; b < K; ++b) {
                if (mask[i] & (1 << b)) {
                    s[K - 1 - b] = '1';
                }
            }
        }
        S[i] = s;
    }

    // Output
    println(N, K);
    for (int i = 0; i < N; ++i) {
        println(S[i]);
    }

    return 0;
}
