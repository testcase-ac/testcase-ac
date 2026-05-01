#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: choose n small, medium, or larger (but hand-verifiable)
    vector<int> n_opts = {5, 10, 20};
    int n = rnd.any(n_opts);
    // Hyper-parameter: choose k either small or moderate
    int k = (rnd.next(0, 1) == 0 ? rnd.next(1, 5) : rnd.next(5, 20));
    // Tolerance factor d between 0 and n-1
    int d = rnd.next(0, n - 1);
    // Number of events m, limited for manual checking
    int m = rnd.next(1, min(50, n * 5));
    vector<int> cnt(n + 1, 0);
    vector<pair<int,int>> events;
    for (int i = 0; i < m; i++) {
        // Check if any group can have departures
        bool canLeave = false;
        for (int r = 1; r <= n - d; r++) {
            if (cnt[r] > 0) { canLeave = true; break; }
        }
        bool doLeave = canLeave && rnd.next() < 0.3;
        if (doLeave) {
            // Pick a random foot size group with current members
            vector<int> nz;
            for (int r = 1; r <= n - d; r++) {
                if (cnt[r] > 0) nz.push_back(r);
            }
            int r = rnd.any(nz);
            int x = -rnd.next(1, cnt[r]);
            cnt[r] += x;
            events.emplace_back(r, x);
        } else {
            // New members join
            int r = rnd.next(1, n - d);
            int x = rnd.next(1, 5);
            cnt[r] += x;
            events.emplace_back(r, x);
        }
    }
    // Output the generated test case
    println(n, m, k, d);
    for (auto &e : events) {
        println(e.first, e.second);
    }
    return 0;
}
