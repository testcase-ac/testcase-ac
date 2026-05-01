#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: sometimes small, medium, or a bit larger
    int N;
    int nt = rnd.next(0, 2);
    if (nt == 0) {
        // small N
        N = rnd.next(1, 5);
    } else if (nt == 1) {
        // medium N
        N = rnd.next(6, 15);
    } else {
        // larger N (still manageable)
        N = rnd.next(16, 20);
    }

    // Hyper-parameter for M: at least 1, up to min(20, total intervals)
    int maxIntervals = N * (N + 1) / 2;
    int maxM = min(20, maxIntervals);
    // use weighted next to bias towards smaller or larger M
    int M = rnd.wnext(maxM, rnd.next(0, 1) ? -1 : 1) + 1;

    // Generate array with different distributions
    vector<int> a(N);
    int distType = rnd.next(0, 2);
    if (distType == 0) {
        // uniform [1,1000]
        for (int i = 0; i < N; i++)
            a[i] = rnd.next(1, 1000);
    } else if (distType == 1) {
        // skewed towards small values [1,1000]
        for (int i = 0; i < N; i++)
            a[i] = rnd.wnext(1000, -2) + 1;
    } else {
        // many repeats of one base value
        int base = rnd.next(1, 1000);
        for (int i = 0; i < N; i++)
            a[i] = (rnd.next() < 0.7 ? base : rnd.next(1, 1000));
    }

    // Output N and M
    println(N, M);
    // Output the array
    println(a);

    // Generate M queries with edge and random cases
    for (int qi = 0; qi < M; qi++) {
        int mode = rnd.next(0, 4);
        int i, j;
        if (mode == 0) {
            // full range
            i = 1; j = N;
        } else if (mode == 1) {
            // single element
            i = rnd.next(1, N);
            j = i;
        } else if (mode == 2) {
            // arbitrary valid
            i = rnd.next(1, N);
            j = rnd.next(i, N);
        } else if (mode == 3) {
            // small prefix
            int len = rnd.next(1, min(5, N));
            i = 1; j = len;
        } else {
            // small suffix
            int len = rnd.next(1, min(5, N));
            j = N; i = N - len + 1;
        }
        println(i, j);
    }

    return 0;
}
