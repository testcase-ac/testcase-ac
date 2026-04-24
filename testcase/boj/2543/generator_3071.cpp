#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of robots (small for hand‐checking)
    int N = rnd.next(1, 10);

    // Choose coordinate upper bound hyper‐parameter
    int loRange = 2 * N;
    int hiRange = 4 * N + rnd.next(0, 10);
    int MAX_COORD = rnd.next(loRange, hiRange);

    // Generate 2*N distinct coordinates in [0, MAX_COORD]
    vector<int> coords(MAX_COORD + 1);
    iota(coords.begin(), coords.end(), 0);
    shuffle(coords.begin(), coords.end());
    coords.resize(2 * N);
    sort(coords.begin(), coords.end());

    // Split into left and right endpoints
    vector<int> L(coords.begin(), coords.begin() + N);
    vector<int> R(coords.begin() + N, coords.end());

    // Randomly match lefts to rights
    shuffle(R.begin(), R.end());
    vector<pair<int,int>> intervals;
    intervals.reserve(N);
    for (int i = 0; i < N; i++) {
        int l = L[i], r = R[i];
        if (l > r) swap(l, r);
        intervals.emplace_back(l, r);
    }

    // Shuffle the interval order
    shuffle(intervals.begin(), intervals.end());

    // Output
    println(N);
    for (auto &pr : intervals) {
        println(pr.first, pr.second);
    }

    return 0;
}
