#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N in a hand-verifiable range
    int N = rnd.next(3, 20);

    // Prepare base ascending permutation
    vector<int> perm(N);
    for (int i = 0; i < N; i++) perm[i] = i + 1;

    // Select a pattern type for variability
    int type = rnd.next(0, 6);

    switch (type) {
        case 0:
            // Fully random
            shuffle(perm.begin(), perm.end());
            break;
        case 1:
            // Strict ascending: 1,2,...,N
            // nothing to do
            break;
        case 2:
            // Strict descending
            reverse(perm.begin(), perm.end());
            break;
        case 3: {
            // Ascending with a few random swaps
            int k = rnd.next(1, max(1, N/4));
            for (int i = 0; i < k; i++) {
                int x = rnd.next(0, N-1);
                int y = rnd.next(0, N-1);
                swap(perm[x], perm[y]);
            }
            break;
        }
        case 4: {
            // Descending with a few random swaps
            reverse(perm.begin(), perm.end());
            int k = rnd.next(1, max(1, N/4));
            for (int i = 0; i < k; i++) {
                int x = rnd.next(0, N-1);
                int y = rnd.next(0, N-1);
                swap(perm[x], perm[y]);
            }
            break;
        }
        case 5: {
            // Perfect zigzag: low, high, next low, next high, ...
            vector<int> tmp;
            int lo = 1, hi = N;
            while (lo <= hi) {
                tmp.push_back(lo++);
                if (lo <= hi) tmp.push_back(hi--);
            }
            perm = tmp;
            break;
        }
        case 6: {
            // Single-cycle shift: 2,3,...,N,1
            for (int i = 0; i < N-1; i++) perm[i] = i+2;
            perm[N-1] = 1;
            break;
        }
    }

    // Output the test case
    println(N);
    println(perm);

    return 0;
}
