#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: sizes
    int N = rnd.next(1, 10);
    int K = rnd.next(1, 10);

    // Hyper-parameter: choose angle range type
    int rc = rnd.next(0, 2);
    int lo, hi;
    if (rc == 0) { lo = 1; hi = 30; }
    else if (rc == 1) { lo = 1; hi = 90; }
    else { lo = 1; hi = 359; }

    // Generate N unique base angles
    set<int> baseSet;
    while ((int)baseSet.size() < N) {
        baseSet.insert(rnd.next(lo, hi));
    }
    vector<int> angles(baseSet.begin(), baseSet.end());
    shuffle(angles.begin(), angles.end());

    // Build one-step closure (sums and absolute diffs)
    set<int> closure1(baseSet.begin(), baseSet.end());
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int a = angles[i], b = angles[j];
            if (a + b < 360) closure1.insert(a + b);
            closure1.insert(abs(a - b));
        }
    }

    // Generate targets
    vector<int> targets;
    for (int i = 0; i < K; i++) {
        if (rnd.next() < 0.5) {
            // Make a solvable target by chaining 1-3 ops
            int ops = rnd.next(1, 3);
            int cur = rnd.any(angles);
            for (int t = 1; t < ops; t++) {
                int a = rnd.any(angles);
                bool doAdd = rnd.next() < 0.5;
                if (doAdd && cur + a < 360) {
                    cur += a;
                } else if (!doAdd && cur >= a) {
                    cur -= a;
                } else {
                    // fallback to abs diff
                    cur = abs(cur - a);
                }
            }
            targets.push_back(cur);
        } else {
            // Try to pick an unsolvable by avoiding one-step closure
            int x;
            do {
                x = rnd.next(1, 359);
            } while (closure1.count(x));
            targets.push_back(x);
        }
    }

    // Output
    println(N, K);
    println(angles);
    println(targets);

    return 0;
}
