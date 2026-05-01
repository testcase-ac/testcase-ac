#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of butters
    int N = rnd.next(2, 10);
    // Mode: sparse gaps (likely forever) or dense (likely finite)
    bool sparse = rnd.next(0, 1) == 0;
    // Starting position
    ll base = rnd.next(-20, 20);
    ll cur = base;
    vector<pair<ll, int>> a;
    for (int i = 0; i < N; i++) {
        if (i > 0) {
            int gap;
            if (sparse) {
                // Ensure final coverage intervals do not overlap: radii up to 7+7=14, so gap >=15
                gap = rnd.next(15, 30);
            } else {
                // Dense gaps to force overlaps
                gap = rnd.next(1, 10);
            }
            cur += gap;
        }
        // Height: odd, include some 1's
        int h;
        if (rnd.next(0, 4) == 0) {
            h = 1;
        } else {
            // heights up to 15
            h = 2 * rnd.next(1, 7) + 1;
        }
        a.emplace_back(cur, h);
    }
    // Shuffle input order
    shuffle(a.begin(), a.end());
    // Output
    println(N);
    for (auto &p : a) {
        println(p.first, p.second);
    }
    return 0;
}
