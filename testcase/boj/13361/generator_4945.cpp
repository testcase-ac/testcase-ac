#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of plates
    int n = rnd.next(1, 10);
    // generate n distinct max-widths t
    set<int> used;
    vector<int> ts;
    while ((int)ts.size() < n) {
        int t = rnd.next(1, 1000000000);
        if (!used.count(t)) {
            used.insert(t);
            ts.push_back(t);
        }
    }
    // sort descending so t[0] > t[1] > ...
    sort(ts.begin(), ts.end(), greater<int>());

    // build plates with s <= t, ensure valid decreasing-width sequence using widths = t
    vector<pair<int,int>> plates;
    for (int t : ts) {
        int half = t / 2;
        int s;
        // with some probability pick s in [half, t] for tricky cases
        if (t > 1 && rnd.next(0.0, 1.0) < 0.3) {
            int lo = max(1, half);
            s = rnd.next(lo, t);
        } else {
            int hi = max(1, half);
            s = rnd.next(1, hi);
        }
        plates.emplace_back(s, t);
    }

    // shuffle input order
    shuffle(plates.begin(), plates.end());
    // output
    println(n);
    for (auto &p : plates) {
        println(p.first, p.second);
    }
    return 0;
}
