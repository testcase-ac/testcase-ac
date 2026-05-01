#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 4);
    println(T);

    int bigIdx = rnd.next(0, T - 1);

    for (int tc = 0; tc < T; ++tc) {
        bool isBig = (tc == bigIdx);
        int n = isBig ? rnd.next(2, 5) : rnd.next(1, 8);

        int S;
        vector<int> t(n), v(n);

        if (!isBig) {
            int type = rnd.next(0, 5);
            if (n == 1 && (type == 3 || type == 4))
                type = 0;

            if (type == 0) {
                // General small random
                S = rnd.next(1, 40);
                for (int i = 0; i < n; ++i) {
                    t[i] = rnd.next(1, 40);
                    v[i] = rnd.next(1, 30);
                }
            } else if (type == 1) {
                // All tasks released before S
                S = rnd.next(10, 50);
                for (int i = 0; i < n; ++i) {
                    t[i] = rnd.next(1, S);
                    v[i] = rnd.next(1, 30);
                }
            } else if (type == 2) {
                // All tasks released after S
                S = rnd.next(1, 20);
                for (int i = 0; i < n; ++i) {
                    t[i] = rnd.next(S + 1, S + 20);
                    v[i] = rnd.next(1, 30);
                }
            } else if (type == 3) {
                // Mixed before/after S
                if (n == 1) {
                    S = rnd.next(1, 40);
                    t[0] = rnd.next(1, 40);
                    v[0] = rnd.next(1, 30);
                } else {
                    S = rnd.next(5, 40);
                    int beforeCnt = rnd.next(1, n - 1);
                    vector<pair<int,int>> hw;
                    hw.reserve(n);
                    for (int i = 0; i < beforeCnt; ++i) {
                        int ti = rnd.next(1, S);
                        int vi = rnd.next(1, 30);
                        hw.push_back({ti, vi});
                    }
                    for (int i = beforeCnt; i < n; ++i) {
                        int ti = rnd.next(S + 1, S + 20);
                        int vi = rnd.next(1, 30);
                        hw.push_back({ti, vi});
                    }
                    shuffle(hw.begin(), hw.end());
                    for (int i = 0; i < n; ++i) {
                        t[i] = hw[i].first;
                        v[i] = hw[i].second;
                    }
                }
            } else if (type == 4) {
                // Few distinct release times (ties)
                S = rnd.next(1, 40);
                int groups = rnd.next(1, min(3, n));
                vector<int> times(groups);
                for (int g = 0; g < groups; ++g)
                    times[g] = rnd.next(1, 40);
                for (int i = 0; i < n; ++i) {
                    t[i] = rnd.any(times);
                    v[i] = rnd.next(1, 30);
                }
            } else { // type == 5
                // Monotone t with correlated v (heavy early or late)
                S = rnd.next(1, 40);
                vector<pair<int,int>> hw(n);
                int start = rnd.next(1, 20);
                int stepMax = 3;
                for (int i = 0; i < n; ++i) {
                    int step = (stepMax == 0 ? 0 : rnd.next(0, stepMax));
                    hw[i].first = start + i * step;
                    if (hw[i].first < 1) hw[i].first = 1;
                }
                bool heavyLate = rnd.next(0, 1);
                int baseV = rnd.next(1, 10);
                if (heavyLate) {
                    for (int i = 0; i < n; ++i)
                        hw[i].second = baseV + i * rnd.next(0, 5);
                } else {
                    for (int i = 0; i < n; ++i)
                        hw[i].second = baseV + (n - 1 - i) * rnd.next(0, 5);
                }
                if (rnd.next(0, 1))
                    shuffle(hw.begin(), hw.end());
                for (int i = 0; i < n; ++i) {
                    t[i] = hw[i].first;
                    v[i] = hw[i].second;
                }
            }
        } else {
            // Big-valued test (to stress 64-bit handling)
            int type = rnd.next(0, 2);
            if (type == 0) {
                // General big random
                S = rnd.next(1, 1000000000);
                for (int i = 0; i < n; ++i) {
                    t[i] = rnd.next(1, 1000000000);
                    v[i] = rnd.next(1, 40000);
                }
            } else if (type == 1) {
                // All before large S
                S = rnd.next(500000000, 1000000000);
                for (int i = 0; i < n; ++i) {
                    t[i] = rnd.next(1, S);
                    v[i] = rnd.next(1, 40000);
                }
            } else { // type == 2
                // One very heavy, late job
                S = rnd.next(1, 1000000000);
                int heavy = rnd.next(0, n - 1);
                int hiCap = 1000000000;
                for (int i = 0; i < n; ++i) {
                    if (i == heavy) {
                        int hi = S + 1000000;
                        if (hi > hiCap) hi = hiCap;
                        if (S > hi) S = hi; // safeguard, though should not happen
                        t[i] = rnd.next(S, hi);
                        v[i] = rnd.next(35000, 40000);
                    } else {
                        if (rnd.next(0, 1)) {
                            t[i] = rnd.next(1, S);
                        } else {
                            int lo = S;
                            int hi = S + 1000000;
                            if (hi > hiCap) hi = hiCap;
                            if (lo > hi) lo = hi; // safeguard
                            t[i] = rnd.next(lo, hi);
                        }
                        v[i] = rnd.next(1, 5000);
                    }
                }
                vector<pair<int,int>> hw(n);
                for (int i = 0; i < n; ++i) hw[i] = {t[i], v[i]};
                shuffle(hw.begin(), hw.end());
                for (int i = 0; i < n; ++i) {
                    t[i] = hw[i].first;
                    v[i] = hw[i].second;
                }
            }
        }

        println(n, S);
        println(t);
        println(v);
    }

    return 0;
}
