#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N to get varied small/medium sizes
    int N;
    if (rnd.next(0, 9) == 0) {
        N = 2;
    } else if (rnd.next(0, 3) == 0) {
        N = rnd.next(3, 5);
    } else if (rnd.next(0, 3) == 0) {
        N = rnd.next(6, 10);
    } else {
        N = rnd.next(11, 30);
    }

    // Precompute primes up to 1000
    vector<int> primes;
    {
        vector<bool> is(1001, true);
        is[0] = is[1] = false;
        for (int i = 2; i <= 1000; ++i) {
            if (is[i]) {
                primes.push_back(i);
                if ((long long)i * i <= 1000)
                    for (int j = i * i; j <= 1000; j += i)
                        is[j] = false;
            }
        }
    }

    vector<int> xs;
    int pattern = rnd.next(1, 4);
    if (pattern == 1) {
        // Completely random distinct values
        int lo = max(N * 2, 50);
        int hi = 1000000;
        set<int> s;
        while ((int)s.size() < N) {
            s.insert(rnd.next(lo, hi));
        }
        xs.assign(s.begin(), s.end());
    } else if (pattern == 2) {
        // Chain of multiples to force many wins/losses
        int Bmax = max(1, 1000000 / N);
        int B = rnd.next(1, Bmax);
        for (int i = 1; i <= N; ++i) {
            xs.push_back(B * i);
        }
    } else if (pattern == 3) {
        // All primes -> likely all draws
        shuffle(primes.begin(), primes.end());
        for (int i = 0; i < N; ++i) {
            xs.push_back(primes[i]);
        }
    } else {
        // Mixed: some primes, some composites (multiples of 6)
        shuffle(primes.begin(), primes.end());
        int k = rnd.next(1, N - 1);
        for (int i = 0; i < k; ++i) {
            xs.push_back(primes[i]);
        }
        for (int i = 1; i <= N - k; ++i) {
            xs.push_back(6 * i);
        }
    }

    // Final shuffle to randomize order
    shuffle(xs.begin(), xs.end());

    // Output
    println(N);
    println(xs);

    return 0;
}
