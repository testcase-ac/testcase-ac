#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // N between 1 and 15, biased sometimes to small or large
    int bias = rnd.next(-1, 1);  // -1: small, 0: uniform, 1: large
    int N = rnd.wnext(15, bias) + 1;

    // Number of colors between 1 and N
    int C = rnd.next(1, N);

    // Assign at least one point per color, then random
    vector<int> y(N);
    for (int i = 0; i < C; ++i) {
        y[i] = i + 1;
    }
    for (int i = C; i < N; ++i) {
        y[i] = rnd.next(1, C);
    }
    // Shuffle color assignments
    shuffle(y.begin(), y.end());

    // Decide coordinate distribution: uniform or clustered
    int distType = rnd.next(0, 1);
    vector<int> x(N);
    if (distType == 0) {
        // Uniform over [0,1000]
        vector<int> cand(1001);
        for (int i = 0; i <= 1000; ++i) cand[i] = i;
        shuffle(cand.begin(), cand.end());
        for (int i = 0; i < N; ++i) x[i] = cand[i];
    } else {
        // Clustered: pick a base, then take from base..base+2*N-1
        int base = rnd.next(0, 1000 - 2 * N);
        vector<int> cand(2 * N);
        for (int i = 0; i < 2 * N; ++i) cand[i] = base + i;
        shuffle(cand.begin(), cand.end());
        for (int i = 0; i < N; ++i) x[i] = cand[i];
    }

    // Combine points and shuffle order
    vector<pair<int,int>> pts(N);
    for (int i = 0; i < N; ++i) {
        pts[i] = { x[i], y[i] };
    }
    shuffle(pts.begin(), pts.end());

    // Output
    println(N);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
