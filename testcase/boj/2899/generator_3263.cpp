#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small N and K
    int N = rnd.next(1, 10);
    int K = rnd.next(2, 5);
    // Choose a small palette of colors
    int maxCol = rnd.next(1, min(N+1, 5));
    vector<int> palette;
    for (int c = 1; c <= maxCol; c++) palette.push_back(c);

    vector<int> a;
    a.reserve(N);

    // 20% chance to start with a run that is already >= K (auto-removable initially)
    if (rnd.next() < 0.2 && N >= K) {
        int runColor = rnd.any(palette);
        int runLen = rnd.next(K, N);
        // fill the prefix
        for (int i = 0; i < runLen; i++) a.push_back(runColor);
        // fill the rest randomly
        for (int i = runLen; i < N; i++) {
            a.push_back(rnd.any(palette));
        }
    } else {
        // Generate with random run breaks
        double changeProb = rnd.next(); // in [0,1)
        for (int i = 0; i < N; i++) {
            if (i == 0 || rnd.next() < changeProb) {
                // start a new run
                a.push_back(rnd.any(palette));
            } else {
                // continue previous run
                a.push_back(a[i-1]);
            }
        }
    }

    // Output
    println(N, K);
    println(a);
    return 0;
}
