#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MIN_S = 1000;
    const int MAX_S = 1000000;
    const int MAX_N = 40;

    vector<int> a;

    int mode = rnd.next(0, 7);

    switch (mode) {
        case 0: {
            // Very small random
            int N = rnd.next(1, 5);
            a.reserve(N);
            for (int i = 0; i < N; ++i)
                a.push_back(rnd.next(MIN_S, MAX_S));
            break;
        }
        case 1: {
            // Boundary patterns around factor 2: x, 2x-1, 2x, 4x-1, ...
            int targetN = rnd.next(5, 30);
            while ((int)a.size() < targetN && (int)a.size() < MAX_N) {
                int x = rnd.next(MIN_S, 250000); // so that 4x-1 <= 1e6
                if ((int)a.size() < MAX_N) a.push_back(x);
                if ((int)a.size() < MAX_N) a.push_back(2 * x - 1);
                if ((int)a.size() < MAX_N && 2 * x <= MAX_S) a.push_back(2 * x);
                if ((int)a.size() < MAX_N && 4 * x - 1 <= MAX_S) a.push_back(4 * x - 1);
            }
            if ((int)a.size() > MAX_N) a.resize(MAX_N);
            break;
        }
        case 2: {
            // All books can fit on a single page (sorted, ratio < 2 throughout)
            int N = rnd.next(5, 30);
            a.reserve(N);
            int cur = rnd.next(MIN_S, 2000);
            a.push_back(cur);
            for (int i = 1; i < N; ++i) {
                long long lo = cur;
                long long hi = min( (long long)MAX_S, 2LL * cur - 1 );
                int nxt = (int)rnd.next((int)lo, (int)hi);
                a.push_back(nxt);
                cur = nxt;
            }
            break;
        }
        case 3: {
            // Each new element forces a new page (values roughly double)
            int targetN = rnd.next(5, 20);
            int cur = rnd.next(MIN_S, 2000);
            a.push_back(cur);
            while ((int)a.size() < targetN) {
                long long cand = 2LL * cur + rnd.next(0, 5);
                if (cand > MAX_S) break;
                a.push_back((int)cand);
                cur = (int)cand;
            }
            // If too short, pad with safe high values that still force new pages
            while ((int)a.size() < 2) {
                int extra = rnd.next(max(cur * 2, MIN_S), MAX_S);
                a.push_back(extra);
            }
            break;
        }
        case 4: {
            // All prices equal
            int N = rnd.next(5, 30);
            a.reserve(N);
            int val = rnd.next(MIN_S, MAX_S);
            for (int i = 0; i < N; ++i) a.push_back(val);
            break;
        }
        case 5: {
            // Random unsorted with many extremes
            int N = rnd.next(10, MAX_N);
            a.reserve(N);
            for (int i = 0; i < N; ++i) {
                int t = rnd.next(0, 3);
                if (t == 0) a.push_back(MIN_S);
                else if (t == 1) a.push_back(MAX_S);
                else a.push_back(rnd.next(MIN_S, MAX_S));
            }
            break;
        }
        case 6: {
            // Clustered groups, each cluster fits on a page, clusters can't be combined
            int G = rnd.next(2, 4);
            int total = 0;
            int base = rnd.next(MIN_S, 2000);
            vector<vector<int>> groups;

            for (int g = 0; g < G && total < MAX_N; ++g) {
                int remaining = MAX_N - total;
                if (remaining <= 0) break;
                int sz = rnd.next(1, min(5, remaining));

                // Ensure next cluster base is far enough to conflict with previous cluster
                if (g > 0) {
                    long long nextBase = max((long long)base * 2 + rnd.next(0, 10), (long long)base + 1);
                    if (nextBase > MAX_S - 1000) break;
                    base = (int)nextBase;
                }

                vector<int> grp;
                int lo = base;
                int hi = (int)min( (long long)MAX_S, 2LL * base - 1 );
                for (int i = 0; i < sz; ++i) {
                    int v = rnd.next(lo, hi);
                    grp.push_back(v);
                    total++;
                }
                groups.push_back(grp);
            }

            // Interleave groups to make ordering non-trivial
            bool any = true;
            int gcount = (int)groups.size();
            vector<int> idx(gcount, 0);
            while (any) {
                any = false;
                for (int g = 0; g < gcount; ++g) {
                    if (idx[g] < (int)groups[g].size()) {
                        a.push_back(groups[g][idx[g]++]);
                        any = true;
                    }
                }
            }
            if (a.empty()) {
                a.push_back(MIN_S);
            }
            break;
        }
        case 7: {
            // Extremes and boundary values
            int N = rnd.next(2, 10);
            a.push_back(MIN_S);
            a.push_back(MAX_S);
            while ((int)a.size() < N) {
                int t = rnd.next(0, 3);
                if (t == 0) {
                    a.push_back(MIN_S);
                } else if (t == 1) {
                    a.push_back(MAX_S);
                } else {
                    int x = rnd.next(MIN_S, 500000);
                    if (rnd.next(0, 1) == 0) {
                        int v = 2 * x - 1;
                        if (v >= MIN_S && v <= MAX_S) a.push_back(v);
                    } else {
                        int v = 2 * x;
                        if (v >= MIN_S && v <= MAX_S) a.push_back(v);
                    }
                }
            }
            break;
        }
    }

    if (a.empty()) {
        a.push_back(MIN_S);
    }

    // Global post-processing for input-order diversity
    double r = rnd.next();
    if (r < 0.33) {
        sort(a.begin(), a.end());
    } else if (r < 0.66) {
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
    } else {
        shuffle(a.begin(), a.end());
    }

    // Output
    println((int)a.size());
    println(a);

    return 0;
}
