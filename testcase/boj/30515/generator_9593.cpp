#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

struct Query {
    int type;
    int l;
    int r;
    int k; // only used for type 1
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXV = 1000;

    // Choose scenario
    int scenario = rnd.next(1, 4);
    int N, Q;
    int deleteProb; // percentage of queries that are type 2

    if (scenario == 1) {
        N = rnd.next(1, 5);
        Q = rnd.next(1, 6);
        deleteProb = rnd.next(0, 30);
    } else if (scenario == 2) {
        N = rnd.next(5, 10);
        Q = rnd.next(5, 15);
        deleteProb = rnd.next(20, 60);
    } else if (scenario == 3) {
        N = rnd.next(10, 15);
        Q = rnd.next(10, 20);
        deleteProb = rnd.next(40, 80);
    } else {
        N = rnd.next(1, 2);
        Q = rnd.next(5, 15);
        deleteProb = rnd.next(30, 70);
    }

    // Generate array A
    vector<int> A(N);
    int arrPattern = rnd.next(1, 4);

    if (arrPattern == 1) {
        // Constant array
        int v = rnd.next(1, MAXV);
        for (int i = 0; i < N; i++) A[i] = v;
    } else if (arrPattern == 2) {
        // Small set of distinct values
        int D = min(rnd.next(2, 4), N);
        set<int> used;
        vector<int> vals;
        while ((int)vals.size() < D) {
            int x = rnd.next(1, MAXV);
            if (!used.count(x)) {
                used.insert(x);
                vals.push_back(x);
            }
        }
        for (int i = 0; i < N; i++) {
            A[i] = rnd.any(vals);
        }
    } else if (arrPattern == 3) {
        // Fully random values
        for (int i = 0; i < N; i++) A[i] = rnd.next(1, MAXV);
    } else {
        // Repeating pattern
        int D = min(rnd.next(1, 5), N);
        for (int i = 0; i < N; i++) {
            A[i] = (i % D) + 1;
        }
    }

    set<int> distinctSet(A.begin(), A.end());
    vector<bool> alive(N, true);

    vector<Query> queries;
    queries.reserve(Q);
    bool hasType1 = false;

    for (int qi = 0; qi < Q; qi++) {
        // Build alive and dead segments
        vector<pair<int,int>> aliveSeg, deadSeg;

        // alive segments
        for (int i = 0; i < N; ) {
            if (alive[i]) {
                int j = i;
                while (j + 1 < N && alive[j + 1]) j++;
                aliveSeg.push_back({i + 1, j + 1});
                i = j + 1;
            } else {
                i++;
            }
        }
        // dead segments
        for (int i = 0; i < N; ) {
            if (!alive[i]) {
                int j = i;
                while (j + 1 < N && !alive[j + 1]) j++;
                deadSeg.push_back({i + 1, j + 1});
                i = j + 1;
            } else {
                i++;
            }
        }

        int l, r;
        int rangeMode = rnd.next(0, 3);
        bool chosen = false;

        if (rangeMode == 0 && !deadSeg.empty()) {
            auto seg = rnd.any(deadSeg);
            l = rnd.next(seg.first, seg.second);
            r = rnd.next(l, seg.second);
            chosen = true;
        } else if (rangeMode == 1 && !aliveSeg.empty()) {
            auto seg = rnd.any(aliveSeg);
            l = rnd.next(seg.first, seg.second);
            r = rnd.next(l, seg.second);
            chosen = true;
        }

        if (!chosen) {
            int pattern = rnd.next(0, 3);
            if (pattern == 0) {
                l = rnd.next(1, N);
                r = l;
            } else if (pattern == 1) {
                r = rnd.next(1, N);
                l = 1;
            } else if (pattern == 2) {
                l = rnd.next(1, N);
                r = N;
                if (l > r) swap(l, r);
            } else {
                l = rnd.next(1, N);
                r = rnd.next(l, N);
            }
        }

        int type = 1;
        if (rnd.next(1, 100) <= deleteProb) type = 2;

        Query q;
        q.type = type;
        q.l = l;
        q.r = r;
        q.k = 1;

        if (type == 1) {
            hasType1 = true;
            int k;
            int chooseType = rnd.next(0, 99);
            if (chooseType < 60) {
                int pos = rnd.next(l, r);
                k = A[pos - 1];
            } else if (chooseType < 80) {
                k = A[rnd.next(0, N - 1)];
            } else {
                int attempts = 0;
                do {
                    k = rnd.next(1, MAXV);
                    attempts++;
                } while (distinctSet.count(k) && attempts < 100);
            }
            q.k = k;
        } else {
            // apply deletion to alive[]
            for (int i = l - 1; i <= r - 1; i++) {
                alive[i] = false;
            }
        }

        queries.push_back(q);
    }

    // Ensure at least one type 1 query
    if (!hasType1) {
        Query &last = queries.back();
        last.type = 1;
        last.k = A[rnd.next(0, N - 1)];
    }

    // Output
    println(N);
    println(A);
    println(Q);
    for (const auto &q : queries) {
        if (q.type == 1) {
            println(q.type, q.l, q.r, q.k);
        } else {
            println(q.type, q.l, q.r);
        }
    }

    return 0;
}
