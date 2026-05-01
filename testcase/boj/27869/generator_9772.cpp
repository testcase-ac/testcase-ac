#include "testlib.h"
using namespace std;

struct Op {
    int t;
    int a;
    int b;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int Nmax = 25;
    const int Qmax = 40;

    // Choose N with bias toward small values
    int N;
    double probN = rnd.next();
    if (probN < 0.2) {
        N = 1;
    } else if (probN < 0.6) {
        N = rnd.next(2, 7);
    } else {
        N = rnd.next(2, Nmax);
    }

    // Generate E_i with several patterns
    vector<long long> E(N);
    int vp = rnd.next(0, 3);
    if (vp == 0) {
        // All ones
        for (int i = 0; i < N; i++) E[i] = 1;
    } else if (vp == 1) {
        // Increasing sequence
        for (int i = 0; i < N; i++) E[i] = i + 1;
    } else if (vp == 2) {
        // Small random values
        for (int i = 0; i < N; i++) E[i] = rnd.next(1, 10);
    } else {
        // Random with a few large spikes
        for (int i = 0; i < N; i++) E[i] = rnd.next(1, 1000);
        int kBig = rnd.next(1, min(N, 3));
        vector<int> idx(N);
        for (int i = 0; i < N; i++) idx[i] = i;
        shuffle(idx.begin(), idx.end());
        for (int i = 0; i < kBig; i++) {
            E[idx[i]] = rnd.next(100000000, 1000000000);
        }
    }

    // Helper to add a random query
    auto addQueryRandom = [&](vector<Op> &ops) {
        int s = rnd.next(1, N);
        int e = rnd.next(s, N);
        ops.push_back({2, s, e});
    };

    vector<Op> ops;

    // Choose scenario type for operation pattern
    int scenarioType = rnd.next(0, 5);

    if (scenarioType == 0) {
        // Tiny, hand-checkable style: a few queries around a single reset
        if (N == 1) {
            int numQ = rnd.next(1, 4);
            for (int i = 0; i < numQ; i++) {
                ops.push_back({2, 1, 1});
            }
        } else {
            int dMid = rnd.next(1, N - 1);
            // Some queries before reset
            ops.push_back({2, 1, N});
            if (rnd.next(0, 1)) {
                int e = rnd.next(1, N);
                ops.push_back({2, 1, e});
            }
            // Reset in the middle
            ops.push_back({1, dMid, 0});
            // Queries after reset
            ops.push_back({2, 1, N});
            if (rnd.next(0, 1)) addQueryRandom(ops);
        }
    } else if (scenarioType == 1) {
        // No resets, only queries
        int numQ = rnd.next(1, Qmax);
        for (int i = 0; i < numQ; i++) {
            addQueryRandom(ops);
        }
    } else if (scenarioType == 2) {
        // All resets first, then queries
        if (N == 1) {
            int numQ = rnd.next(1, Qmax);
            for (int i = 0; i < numQ; i++) {
                ops.push_back({2, 1, 1});
            }
        } else {
            int maxRes = N - 1;
            int kResets = rnd.next(1, maxRes);
            vector<int> ds(maxRes);
            for (int i = 0; i < maxRes; i++) ds[i] = i + 1;
            shuffle(ds.begin(), ds.end());
            for (int i = 0; i < kResets; i++) {
                ops.push_back({1, ds[i], 0});
            }
            int remaining = Qmax - (int)ops.size();
            int numQ = rnd.next(1, max(1, min(15, remaining)));
            for (int i = 0; i < numQ; i++) {
                addQueryRandom(ops);
            }
        }
    } else if (scenarioType == 3) {
        // Interleaved random resets and queries
        int targetOps = rnd.next(3, Qmax - 1);
        vector<int> ds;
        int maxRes = max(0, N - 1);
        for (int i = 1; i <= maxRes; i++) ds.push_back(i);
        shuffle(ds.begin(), ds.end());
        int usedResets = 0;
        while ((int)ops.size() < targetOps) {
            bool canReset = (N >= 2 && usedResets < (int)ds.size());
            if (canReset && rnd.next(0, 1) == 0) {
                ops.push_back({1, ds[usedResets++], 0});
            } else {
                addQueryRandom(ops);
            }
        }
    } else if (scenarioType == 4) {
        // Dense resets, many boundary-focused queries
        if (N == 1) {
            int numQ = rnd.next(1, Qmax);
            for (int i = 0; i < numQ; i++) {
                ops.push_back({2, 1, 1});
            }
        } else {
            int maxRes = N - 1;
            int low = max(1, N - 3);
            int kResets = rnd.next(low, maxRes);
            vector<int> ds(maxRes);
            for (int i = 0; i < maxRes; i++) ds[i] = i + 1;
            shuffle(ds.begin(), ds.end());
            ds.resize(kResets);

            // Ensure 1 and N-1 are included if possible
            auto ensureIn = [&](int val) {
                bool found = false;
                for (int x : ds) if (x == val) { found = true; break; }
                if (!found) {
                    ds[rnd.next(0, kResets - 1)] = val;
                }
            };
            if (kResets >= 1) {
                ensureIn(1);
                if (N - 1 != 1) ensureIn(N - 1);
            }

            // Some structured operations around edges
            bool usedFirst = false, usedLast = false;
            for (int d : ds) {
                if (!usedFirst && d == 1) {
                    ops.push_back({1, d, 0});
                    ops.push_back({2, 1, rnd.next(1, N)});
                    usedFirst = true;
                } else if (!usedLast && d == N - 1) {
                    ops.push_back({1, d, 0});
                    ops.push_back({2, rnd.next(1, N), N});
                    usedLast = true;
                } else {
                    ops.push_back({1, d, 0});
                }
            }

            // Add some more queries spanning various segments
            int remaining = Qmax - (int)ops.size();
            int numQ = rnd.next(1, max(1, min(10, remaining)));
            for (int i = 0; i < numQ; i++) {
                if (rnd.next(0, 2) == 0) {
                    // Whole range
                    ops.push_back({2, 1, N});
                } else {
                    // Random small or medium interval
                    int s = rnd.next(1, N);
                    int e = rnd.next(s, N);
                    ops.push_back({2, s, e});
                }
            }
        }
    } else { // scenarioType == 5
        // Many short-range queries, some resets if possible
        int targetOps = rnd.next(5, Qmax - 1);
        int maxRes = max(0, N - 1);
        vector<int> ds;
        for (int i = 1; i <= maxRes; i++) ds.push_back(i);
        shuffle(ds.begin(), ds.end());
        int maxUseRes = (maxRes == 0 ? 0 : rnd.next(0, min(maxRes, 5)));
        int usedResets = 0;

        while ((int)ops.size() < targetOps) {
            bool canReset = (N >= 2 && usedResets < maxUseRes);
            if (canReset && rnd.next(0, 3) == 0) {
                ops.push_back({1, ds[usedResets++], 0});
            } else {
                // Prefer single-day or very short intervals
                if (N == 1 || rnd.next(0, 2) < 2) {
                    int pos = rnd.next(1, N);
                    ops.push_back({2, pos, pos});
                } else {
                    int len = rnd.next(2, min(3, N));
                    int s = rnd.next(1, N - len + 1);
                    int e = s + len - 1;
                    ops.push_back({2, s, e});
                }
            }
        }
    }

    // Ensure we have at least one operation
    if (ops.empty()) {
        addQueryRandom(ops);
    }

    // Ensure last operation is type 2 (query)
    if (ops.back().t == 1) {
        addQueryRandom(ops);
    }

    int Q = (int)ops.size();

    println(N, Q);
    println(E);

    for (const auto &op : ops) {
        if (op.t == 1) {
            println(1, op.a);
        } else {
            println(2, op.a, op.b);
        }
    }

    return 0;
}
