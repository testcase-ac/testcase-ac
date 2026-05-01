#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose dimensions with total cells <= 50 for readability
    int N = rnd.next(1, 10);
    int M_max = min(10, max(1, 50 / N));
    int M = rnd.next(1, M_max);

    // Pick a pattern type for variability
    int type = rnd.next(0, 4);

    // Prepare the matrix
    vector<vector<long long>> S(N, vector<long long>(M));

    switch (type) {
        // Pattern 0: fully random values from a varying upper bound
        case 0: {
            vector<long long> Ks = {5, 10, 100, 1000000000};
            long long K = rnd.any(Ks);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    S[i][j] = rnd.next(1LL, K);
            break;
        }
        // Pattern 1: strictly increasing row-major
        case 1: {
            long long base = rnd.next(1LL, 20LL);
            long long v = base;
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    S[i][j] = v++;
            break;
        }
        // Pattern 2: strictly increasing column-major
        case 2: {
            long long base = rnd.next(1LL, 20LL);
            long long v = base;
            for (int j = 0; j < M; j++)
                for (int i = 0; i < N; i++)
                    S[i][j] = v++;
            break;
        }
        // Pattern 3: a few equal-value clusters
        case 3: {
            int D = rnd.next(1, min(N * M, 5));
            set<long long> se;
            while ((int)se.size() < D) {
                se.insert(rnd.next(1LL, 20LL));
            }
            vector<long long> vals(se.begin(), se.end());
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    S[i][j] = rnd.any(vals);
            break;
        }
        // Pattern 4: checkerboard of two values
        case 4: {
            long long a = rnd.next(1LL, 20LL);
            long long b;
            do { b = rnd.next(1LL, 20LL); } while (b == a);
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                    S[i][j] = ((i + j) % 2 == 0 ? a : b);
            break;
        }
    }

    // Output the generated test case
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(S[i]);
    }

    return 0;
}
