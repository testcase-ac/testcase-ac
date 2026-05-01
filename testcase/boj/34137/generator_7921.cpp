#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: bias towards smaller Ns
    int N = rnd.wnext(20, -1) + 2;  // N in [2..21], biased low
    // M: number of columns, small for hand-checkable
    int M = rnd.next(2, 15);
    // T: number of colors, mix of small and moderate
    int maxT = min(M, 10);
    int T;
    if (maxT <= 3 || rnd.next(0,1) == 0) {
        T = rnd.next(1, maxT);
    } else {
        T = rnd.wnext(maxT, 1) + 1;
    }

    // Initial colors for each column
    vector<int> a(M);
    for (int i = 0; i < M; i++) {
        a[i] = rnd.next(1, T);
    }

    // Decide how many distinct rows will have structures
    int maxRows = min(N - 1, 5);
    int R = rnd.next(0, maxRows);

    // Pick R distinct rows in [2..N]
    vector<int> possibleRows;
    for (int r = 2; r <= N; r++) possibleRows.push_back(r);
    shuffle(possibleRows.begin(), possibleRows.end());
    possibleRows.resize(R);
    sort(possibleRows.begin(), possibleRows.end());

    struct Struct { int r, s, e, c; };
    vector<Struct> structures;

    // For each chosen row, generate 1..3 disjoint segments
    for (int r : possibleRows) {
        int maxSeg = min(3, M);
        int C = rnd.wnext(maxSeg, -1) + 1;  // number of structures at this row
        // available intervals of columns
        vector<pair<int,int>> intervals;
        intervals.emplace_back(1, M);
        for (int i = 0; i < C && !intervals.empty(); i++) {
            // flatten intervals to pick a random column
            int total = 0;
            for (auto &pr : intervals) total += pr.second - pr.first + 1;
            int idx = rnd.next(0, total - 1);
            int acc = 0;
            int s = -1, availMax = 0;
            int ivIdx = -1;
            for (int j = 0; j < (int)intervals.size(); j++) {
                auto pr = intervals[j];
                int len = pr.second - pr.first + 1;
                if (idx < acc + len) {
                    s = pr.first + (idx - acc);
                    availMax = pr.second - s + 1;
                    ivIdx = j;
                    break;
                }
                acc += len;
            }
            if (s < 0) break;
            int len = rnd.next(1, min(availMax, 3));
            int e = s + len - 1;
            int c = rnd.next(1, T);
            structures.push_back({r, s, e, c});
            // update intervals: remove [s..e]
            auto pr = intervals[ivIdx];
            vector<pair<int,int>> newI;
            if (pr.first < s) newI.emplace_back(pr.first, s - 1);
            if (e < pr.second) newI.emplace_back(e + 1, pr.second);
            intervals.erase(intervals.begin() + ivIdx);
            for (auto &x : newI) intervals.push_back(x);
        }
    }

    // Shuffle structures so they're not ordered by row
    shuffle(structures.begin(), structures.end());

    // Output
    int K = structures.size();
    println(N, M, T, K);
    println(a);
    for (auto &st : structures) {
        println(st.r, st.s, st.e, st.c);
    }

    return 0;
}
