#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose size category
    int sizeType = rnd.next(0, 3);
    int N;
    if (sizeType == 0) {
        N = 1;
    } else if (sizeType == 1) {
        N = rnd.next(2, 10);
    } else if (sizeType == 2) {
        N = rnd.next(11, 30);
    } else {
        N = rnd.next(31, 100);
    }

    // Decide whether to enforce total xor = 0 (losing) or != 0 (winning possible)
    bool enforceZeroXor = (N >= 2 && rnd.next() < 0.3);

    vector<int> P(N);
    if (enforceZeroXor) {
        // Generate first N-1 piles so that xor != 0 and <= 1000
        int s;
        do {
            for (int i = 0; i < N-1; i++) {
                P[i] = rnd.next(1, 1000);
            }
            s = 0;
            for (int i = 0; i < N-1; i++) s ^= P[i];
        } while (s == 0 || s > 1000);
        // Last pile to make total xor zero
        P[N-1] = s;
    } else {
        // Generate all randomly, ensure total xor != 0
        int x;
        do {
            x = 0;
            for (int i = 0; i < N; i++) {
                P[i] = rnd.next(1, 1000);
                x ^= P[i];
            }
            if (x == 0) {
                // Mutate one element to break zero xor
                int k = rnd.next(0, N-1);
                if (P[k] < 1000) P[k]++;
                else P[k]--;
                // recompute xor next loop
            }
        } while (([] (const vector<int>& v) {
            int t = 0;
            for (int x : v) t ^= x;
            return t;
        })(P) == 0);
    }

    // Shuffle to avoid positional bias
    shuffle(P.begin(), P.end());

    // Output
    println(N);
    println(P);

    return 0;
}
