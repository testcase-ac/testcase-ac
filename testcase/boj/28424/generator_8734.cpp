#include "testlib.h"
using namespace std;

struct Query {
    int type; // 1 or 2
    int i;
    long long x; // only for type 1
};

void applyType1(int start, long long x, const vector<long long>& cap, vector<long long>& drank, int N) {
    long long remain = x;
    for (int j = start; j <= N && remain > 0; ++j) {
        if (j < N) {
            long long left = cap[j] - drank[j];
            if (left <= 0) continue;
            long long d = min(left, remain);
            drank[j] += d;
            remain -= d;
        } else { // j == N, special rule
            if (drank[j] >= cap[j]) {
                remain = 0;
                break;
            }
            long long left = cap[j] - drank[j];
            if (remain < left) {
                drank[j] += remain;
                remain = 0;
            } else {
                drank[j] = cap[j];
                remain = 0; // leftover discarded
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 4);

    int N = 0, Q = 0;
    vector<long long> cap;

    if (scenario == 0) {
        // Tiny N, small capacities
        N = rnd.next(1, 3);
        Q = rnd.next(3, 7);
        cap.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            cap[i] = rnd.next(1, 10);
        }
    } else if (scenario == 1) {
        // Medium N, small capacities
        N = rnd.next(4, 8);
        Q = rnd.next(6, 15);
        cap.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            cap[i] = rnd.next(1, 20);
        }
    } else if (scenario == 2) {
        // Few people, some huge capacities to test overflow handling
        N = rnd.next(2, 6);
        Q = rnd.next(5, 15);
        cap.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            if (rnd.next(0, 2) == 0)
                cap[i] = rnd.next(1, 20);                // small
            else
                cap[i] = rnd.next(100000000, 1000000000); // big
        }
    } else if (scenario == 3) {
        // Single person edge case
        N = 1;
        Q = rnd.next(3, 10);
        cap.assign(N + 1, 0);
        if (rnd.next(0, 1) == 0)
            cap[1] = rnd.next(1, 30);
        else
            cap[1] = rnd.next(100000000, 1000000000);
    } else { // scenario == 4
        // Chain of ones / small caps to force quick saturation
        N = rnd.next(5, 12);
        Q = rnd.next(10, 25);
        cap.assign(N + 1, 0);
        for (int i = 1; i <= N; ++i) {
            if (rnd.next(0, 3) == 0)
                cap[i] = rnd.next(2, 5);
            else
                cap[i] = 1;
        }
    }

    vector<long long> drank(N + 1, 0);
    vector<Query> qs;
    qs.reserve(Q);

    int type1Count = 0, type2Count = 0;
    bool bigType1Seen = false; // for scenario 2

    for (int qi = 0; qi < Q; ++qi) {
        int remaining = Q - qi;
        int missing1 = (type1Count == 0 ? 1 : 0);
        int missing2 = (type2Count == 0 ? 1 : 0);

        int type;
        if (remaining == missing1 + missing2) {
            // Must fill missing types
            if (missing1) type = 1;
            else type = 2;
        } else {
            int pType1;
            if (scenario == 3) pType1 = 70;     // more type1 for N=1
            else if (scenario == 2) pType1 = 65;
            else pType1 = 60;
            int r = rnd.next(0, 99);
            type = (r < pType1 ? 1 : 2);
        }

        if (type == 1) {
            int i = rnd.next(1, N);
            long long x = 1;

            if (scenario == 2) {
                int mode = rnd.next(0, 2);
                if (mode == 0) {
                    // Small x
                    x = rnd.next(1LL, 1000LL);
                } else if (mode == 1) {
                    // Target remaining capacity of some k >= i
                    int k = rnd.next(i, N);
                    long long rem = cap[k] - drank[k];
                    if (rem <= 0) rem = 1;
                    long long delta = rnd.next(0LL, 1000000LL);
                    if (rem + delta > 1000000000LL) delta = 1000000000LL - rem;
                    if (delta < 0) delta = 0;
                    x = rem + delta;
                } else {
                    // Large x near upper bound
                    long long lo = 800000000LL;
                    long long hi = 1000000000LL;
                    x = rnd.next(lo, hi);
                }
            } else if (scenario == 3) {
                // N == 1
                long long rem = cap[1] - drank[1];
                if (rem <= 0) rem = 1;
                int mode = rnd.next(0, 2);
                if (mode == 0) {
                    x = rnd.next(1LL, rem * 2 > 0 ? rem * 2 : 1LL);
                    if (x > 1000000000LL) x = 1000000000LL;
                } else if (mode == 1) {
                    x = rem; // exactly fill
                } else {
                    x = rnd.next(1LL, 1000000000LL);
                }
            } else {
                // Small/medium scenarios
                int mode = rnd.next(0, 2);
                if (mode == 0) {
                    x = rnd.next(1LL, 20LL);
                } else if (mode == 1) {
                    int k = rnd.next(i, N);
                    long long rem = cap[k] - drank[k];
                    if (rem <= 0) rem = 1;
                    long long delta = rnd.next(0LL, 5LL);
                    x = rem + delta;
                } else {
                    long long sum = 0;
                    for (int j = i; j <= N; ++j) {
                        long long left = cap[j] - drank[j];
                        if (left > 0) sum += left;
                    }
                    if (sum <= 0) sum = 1;
                    long long extra = rnd.next(0LL, 5LL);
                    x = sum + extra;
                }
                if (x > 1000000000LL) x = 1000000000LL;
            }

            if (x < 1) x = 1;
            if (x > 1000000000LL) x = 1000000000LL;

            if (scenario == 2 && x >= 100000000LL)
                bigType1Seen = true;

            Query q;
            q.type = 1;
            q.i = i;
            q.x = x;
            qs.push_back(q);

            applyType1(i, x, cap, drank, N);
            ++type1Count;
        } else {
            int i;
            if (scenario == 3) {
                i = 1;
            } else {
                // Slight bias towards ends
                int mode = rnd.next(0, 4);
                if (mode == 0) i = 1;
                else if (mode == 1) i = N;
                else i = rnd.next(1, N);
            }
            Query q;
            q.type = 2;
            q.i = i;
            q.x = 0;
            qs.push_back(q);
            ++type2Count;
        }
    }

    // For scenario 2, ensure at least one large x; if not, modify first type1's x (no need to resimulate, validity unaffected)
    if (scenario == 2 && !bigType1Seen) {
        for (int idx = 0; idx < (int)qs.size(); ++idx) {
            if (qs[idx].type == 1) {
                qs[idx].x = rnd.next(800000000LL, 1000000000LL);
                break;
            }
        }
    }

    println(N, Q);
    for (int i = 1; i <= N; ++i) {
        println(cap[i]);
    }
    for (const auto &q : qs) {
        if (q.type == 1)
            println(1, q.i, q.x);
        else
            println(2, q.i);
    }

    return 0;
}
