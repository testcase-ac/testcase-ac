#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Screen and basket sizes
    int N = rnd.next(2, 10);
    int M = rnd.next(1, N - 1);
    int J = rnd.next(1, 20);

    // Decide sequence pattern: 0=uniform, 1=clustered, 2=alternating extremes
    int seqType = rnd.next(0, 2);
    vector<int> apples;
    apples.reserve(J);

    if (seqType == 0) {
        // Uniform random positions
        for (int i = 0; i < J; i++) {
            apples.push_back(rnd.next(1, N));
        }
    } else if (seqType == 1) {
        // Clustered around a few centers
        int k = rnd.next(1, min(3, J));
        vector<int> centers(k), radius(k);
        for (int i = 0; i < k; i++) {
            centers[i] = rnd.next(1, N);
            radius[i] = rnd.next(0, N / 3);
        }
        for (int i = 0; i < J; i++) {
            int idx = rnd.next(0, k - 1);
            int c = centers[idx];
            int r = radius[idx];
            int offset = (r > 0 ? rnd.next(-r, r) : 0);
            int p = c + offset;
            if (p < 1) p = 1;
            if (p > N) p = N;
            apples.push_back(p);
        }
    } else {
        // Alternating between low and high ends
        int k = rnd.next(1, N / 2);
        for (int i = 0; i < J; i++) {
            if (i % 2 == 0) {
                apples.push_back(rnd.next(1, k));
            } else {
                apples.push_back(rnd.next(N - k + 1, N));
            }
        }
    }

    // Output formatted input
    println(N, M);
    println(J);
    for (int x : apples) {
        println(x);
    }

    return 0;
}
