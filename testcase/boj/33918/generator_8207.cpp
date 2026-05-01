#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with variability: small, medium, large
    int N;
    double p = rnd.next();
    if (p < 0.2) {
        N = rnd.next(1, 5);
    } else if (p < 0.7) {
        N = rnd.next(6, 20);
    } else {
        N = rnd.next(21, 50);
    }

    // Choose M; if N is small allow very large M, else cap M to keep output compact
    int M;
    if (N <= 20) {
        if (rnd.next(0, 1) == 0)
            M = rnd.next(1, 1000);
        else
            M = rnd.next(1001, 25000);
    } else {
        M = rnd.next(1, 1000);
    }

    // Choose C, then D as a multiple of C
    int C = rnd.next(1, M);
    int maxK = M / C;
    if (maxK < 1) maxK = 1;
    int mode = rnd.next(0, 2);
    int k;
    if (mode == 0) {
        k = 1;
    } else if (mode == 1) {
        k = maxK;
    } else {
        k = rnd.next(1, maxK);
    }
    int D = C * k;

    // Generate optimal temperatures b[0..N-1] with diverse patterns
    vector<int> b(N);
    int style = rnd.next(0, 6);
    switch (style) {
        case 0: // uniform random
            for (int i = 0; i < N; i++)
                b[i] = rnd.next(1, M);
            break;
        case 1: // cluster low
            for (int i = 0; i < N; i++)
                b[i] = rnd.wnext(M, -3) + 1;
            break;
        case 2: // cluster high
            for (int i = 0; i < N; i++)
                b[i] = rnd.wnext(M, 3) + 1;
            break;
        case 3: { // monotonic increasing
            b[0] = rnd.next(1, M);
            for (int i = 1; i < N; i++) {
                int step = rnd.next(0, M / max(1, N) + 1);
                b[i] = min(M, b[i-1] + step);
            }
            break;
        }
        case 4: { // monotonic decreasing
            b[0] = rnd.next(1, M);
            for (int i = 1; i < N; i++) {
                int step = rnd.next(0, M / max(1, N) + 1);
                b[i] = max(1, b[i-1] - step);
            }
            break;
        }
        case 5: { // few distinct values
            int d = rnd.next(1, min(5, N));
            vector<int> vals(d);
            for (int j = 0; j < d; j++)
                vals[j] = rnd.next(1, M);
            for (int i = 0; i < N; i++)
                b[i] = rnd.any(vals);
            break;
        }
        case 6: { // constant
            int v = rnd.next(1, M);
            for (int i = 0; i < N; i++)
                b[i] = v;
            break;
        }
    }

    // Output
    println(N, M, C, D);
    println(b);

    return 0;
}
