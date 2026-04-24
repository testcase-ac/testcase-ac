#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose small N with varied sizes
    int N;
    int modeN = rnd.next(0, 2);
    if (modeN == 0) {
        // very small
        N = rnd.next(2, 4);
    } else if (modeN == 1) {
        // small-to-medium
        N = rnd.next(5, 8);
    } else {
        // medium
        N = rnd.next(9, 10);
    }

    // Hyper-parameter: maximum coordinate range
    int Xmax = N + rnd.next(0, 10);

    // Hyper-parameter: maximum height options
    vector<int> Hopts = {5, 10, 20, 100};
    int Hmax = rnd.any(Hopts);

    // Generate N distinct positions in [1..Xmax]
    vector<int> xs(Xmax);
    for (int i = 0; i < Xmax; i++) xs[i] = i + 1;
    shuffle(xs.begin(), xs.end());
    xs.resize(N);
    sort(xs.begin(), xs.end());

    // Compute span for D selection
    int span = xs.back() - xs.front();

    // Hyper-parameter: choose D small, medium, or large relative to span
    int dt = rnd.next(0, 2);
    int D;
    if (dt == 0) {
        // small D
        D = rnd.next(1, max(1, span / 4));
    } else if (dt == 1) {
        // medium D
        D = rnd.next(max(1, span / 4 + 1), max(1, span / 2));
    } else {
        // large D
        D = rnd.next(max(1, span / 2 + 1), span * 2 + 1);
    }

    // Assign random heights and build cow list
    vector<pair<int,int>> cows;
    for (int i = 0; i < N; i++) {
        int h = rnd.next(1, Hmax);
        cows.emplace_back(xs[i], h);
    }

    // Shuffle input order (not necessarily sorted by x)
    shuffle(cows.begin(), cows.end());

    // Output
    println(N, D);
    for (auto &p : cows) {
        println(p.first, p.second);
    }

    return 0;
}
