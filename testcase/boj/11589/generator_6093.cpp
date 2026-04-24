#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of sticks
    int N = rnd.next(3, 8);
    const int MAXX = 100, MAXY = 1000;
    // Probability that a new segment overlaps in x with a previous one
    double overlapProb = rnd.next(0.0, 1.0);

    // Choose distinct y-coordinates and sort them (lower y = closer to edge)
    set<int> yset;
    while ((int)yset.size() < N) {
        yset.insert(rnd.next(1, MAXY));
    }
    vector<int> ys(yset.begin(), yset.end());
    sort(ys.begin(), ys.end());

    // Store segments and their x-intervals
    vector<array<int,4>> segs(N);
    vector<pair<int,int>> xint(N);

    for (int k = 0; k < N; k++) {
        int y = ys[k];
        // Decide for each previous segment whether we should overlap in x
        vector<bool> need(N, false);
        for (int i = 0; i < k; i++) {
            need[i] = (rnd.next() < overlapProb);
        }
        // Find an x-interval satisfying all required overlaps/non-overlaps
        int x1, x2;
        for (int trial = 0; trial < 1000; trial++) {
            x1 = rnd.next(0, MAXX - 1);
            int maxLen = MAXX - x1;
            int len = rnd.next(1, min(15, maxLen));
            x2 = x1 + len;
            bool ok = true;
            for (int i = 0; i < k; i++) {
                bool inter = !(x2 < xint[i].first || x1 > xint[i].second);
                if (inter != need[i]) {
                    ok = false;
                    break;
                }
            }
            if (ok) break;
        }
        xint[k] = {x1, x2};
        segs[k] = {x1, y, x2, y};
    }

    // Shuffle input order to randomize labels
    vector<int> perm(N);
    for (int i = 0; i < N; i++) perm[i] = i;
    shuffle(perm.begin(), perm.end());

    // Output
    println(N);
    for (int j = 0; j < N; j++) {
        auto &s = segs[perm[j]];
        println(s[0], s[1], s[2], s[3]);
    }
    return 0;
}
