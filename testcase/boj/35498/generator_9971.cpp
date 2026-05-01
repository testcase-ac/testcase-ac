#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Query {
    int t;
    int l, r;
    long long v;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 4);

    int N = 0, Q = 0;
    vector<long long> A;
    vector<Query> qs;

    // Scenario 0: general random, small/medium
    if (scenario == 0) {
        if (rnd.next(0, 2) == 0)
            N = rnd.next(1, 4);
        else if (rnd.next(0, 1) == 0)
            N = rnd.next(5, 10);
        else
            N = rnd.next(11, 15);

        Q = rnd.next(1, 20);

        A.resize(N);
        for (int i = 0; i < N; ++i)
            A[i] = rnd.next(-20, 20);

        bool haveType2 = false;
        for (int qi = 0; qi < Q; ++qi) {
            if (qi == Q - 1 && !haveType2) {
                qs.push_back({2, 0, 0, 0});
                haveType2 = true;
                continue;
            }
            int choice = rnd.next(0, 99);
            if (choice < 40) {
                qs.push_back({2, 0, 0, 0});
                haveType2 = true;
            } else {
                int l = rnd.next(1, N);
                int r = rnd.next(l, N);
                long long v = rnd.next(-20, 20);
                qs.push_back({1, l, r, v});
            }
        }
    }
    // Scenario 1: N = 1 edge case
    else if (scenario == 1) {
        N = 1;
        Q = rnd.next(1, 15);

        A.resize(1);
        A[0] = rnd.next(-10, 10);

        bool haveType2 = false;
        for (int qi = 0; qi < Q; ++qi) {
            if (qi == Q - 1 && !haveType2) {
                qs.push_back({2, 0, 0, 0});
                haveType2 = true;
                continue;
            }
            int choice = rnd.next(0, 99);
            if (choice < 50) {
                qs.push_back({2, 0, 0, 0});
                haveType2 = true;
            } else {
                long long v = rnd.next(-20, 20);
                qs.push_back({1, 1, 1, v});
            }
        }
    }
    // Scenario 2: always nondecreasing, only full-range updates
    else if (scenario == 2) {
        N = rnd.next(2, 10);
        Q = rnd.next(3, 15);

        A.resize(N);
        long long cur = rnd.next(-10, 10);
        for (int i = 0; i < N; ++i) {
            A[i] = cur;
            cur += rnd.next(0, 5); // nondecreasing
        }

        bool haveType2 = false;
        for (int qi = 0; qi < Q; ++qi) {
            if (qi == Q - 1 && !haveType2) {
                qs.push_back({2, 0, 0, 0});
                haveType2 = true;
                continue;
            }
            int choice = rnd.next(0, 99);
            if (choice < 60) {
                qs.push_back({2, 0, 0, 0});
                haveType2 = true;
            } else {
                long long v = rnd.next(-10, 10);
                qs.push_back({1, 1, N, v});
            }
        }
    }
    // Scenario 3: many overlapping short ranges, borderline array
    else if (scenario == 3) {
        N = rnd.next(2, 8);
        Q = rnd.next(10, 20);

        A.resize(N);
        A[0] = rnd.next(-10, 10);
        for (int i = 1; i < N; ++i) {
            int delta = rnd.next(-1, 1);
            A[i] = A[i - 1] + delta;
        }

        bool haveType2 = false;
        for (int qi = 0; qi < Q; ++qi) {
            if (qi == Q - 1 && !haveType2) {
                qs.push_back({2, 0, 0, 0});
                haveType2 = true;
                continue;
            }
            int tChoice = rnd.next(0, 99);
            if (tChoice < 50) {
                // type 1 with emphasis on short ranges
                int l, r;
                if (N == 1) {
                    l = r = 1;
                } else {
                    int style = rnd.next(0, 99);
                    if (style < 40) {
                        l = r = rnd.next(1, N); // point update
                    } else if (style < 70) {
                        int len = rnd.next(2, min(3, N));
                        l = rnd.next(1, N - len + 1);
                        r = l + len - 1;
                    } else {
                        l = rnd.next(1, N);
                        r = rnd.next(l, N);
                    }
                }
                long long v;
                do {
                    v = rnd.next(-5, 5);
                } while (v == 0 && rnd.next(0, 4) != 0);
                qs.push_back({1, l, r, v});
            } else {
                qs.push_back({2, 0, 0, 0});
                haveType2 = true;
            }
        }
    }
    // Scenario 4: fixed-size N=5 with crafted edges
    else {
        N = 5;
        Q = 8;

        A.assign(N, 0);

        // Crafted sequence of updates and queries to stress boundaries
        qs.clear();
        qs.push_back({1, 1, 3, 1});   // A: [1,1,1,0,0]
        qs.push_back({2, 0, 0, 0});   // check
        qs.push_back({1, 3, 5, 1});   // A: [1,1,2,1,1]
        qs.push_back({2, 0, 0, 0});   // check
        qs.push_back({1, 2, 4, -2});  // A: [1,-1,0,-1,1]
        qs.push_back({2, 0, 0, 0});   // check
        // Two random but boundary-focused updates + final check
        int l1 = 1;
        int r1 = rnd.next(1, N);
        long long v1 = rnd.next(-3, 3);
        qs.push_back({1, l1, r1, v1});
        qs.push_back({2, 0, 0, 0});
    }

    Q = (int)qs.size();

    println(N, Q);
    println(A);

    for (const auto &q : qs) {
        if (q.t == 1) {
            println(q.t, q.l, q.r, q.v);
        } else {
            println(q.t);
        }
    }

    return 0;
}
