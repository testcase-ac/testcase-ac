#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

long long computeSum(int A, int B, const vector<pair<int,int>>& segs) {
    long long res = 0;
    for (auto &pr : segs) {
        int L = pr.first;
        int R = pr.second;
        int left = max(L, A);
        int right = min(R, B);
        if (right > left) res += (right - left);
    }
    return res;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 4);
    int N;
    long long K;
    vector<pair<int,int>> segs;

    if (scenario == 0) {
        // Scenario 0: Single interval, guaranteed solution, small coordinates.
        N = 1;
        int C = rnd.next(5, 40);
        int L = rnd.next(0, C - 1);
        int R = rnd.next(L + 1, C);
        segs.push_back({L, R});

        int A = rnd.next(L, R - 1);
        int B = rnd.next(A + 1, R);
        K = computeSum(A, B, segs); // = B - A, > 0

    } else if (scenario == 1) {
        // Scenario 1: Multiple intervals, small coordinates, crafted patterns, guaranteed solution.
        int C = rnd.next(10, 40);
        int A = rnd.next(1, C - 2);
        int B = rnd.next(A + 1, C - 1);

        N = rnd.next(3, 12);
        segs.clear();

        // First interval: full cover of [A,B]
        {
            int L = rnd.next(0, A);
            int R = rnd.next(B, C);
            segs.push_back({L, R});
        }

        for (int i = 1; i < N; i++) {
            vector<int> kinds;
            // kind 0: full cover (always possible)
            kinds.push_back(0);
            // kind 1: left-partial Li < A < Ri < B
            if (A >= 1 && B - A >= 2) kinds.push_back(1);
            // kind 2: right-partial A < Li < B < Ri
            if (B - A >= 2 && C - B >= 1) kinds.push_back(2);
            // kind 3: inner-sub A <= Li < Ri <= B
            if (B - A >= 1) kinds.push_back(3);
            // kind 4: disjoint-left Ri < A
            if (A >= 2) kinds.push_back(4);
            // kind 5: disjoint-right Li > B
            if (C - B >= 2) kinds.push_back(5);

            int kind = rnd.any(kinds);
            int L, R;
            if (kind == 0) {
                // full cover
                L = rnd.next(0, A);
                R = rnd.next(B, C);
            } else if (kind == 1) {
                // left-partial Li < A < Ri < B
                L = rnd.next(0, A - 1);
                R = rnd.next(A + 1, B - 1);
            } else if (kind == 2) {
                // right-partial A < Li < B < Ri
                L = rnd.next(A + 1, B - 1);
                R = rnd.next(B + 1, C);
            } else if (kind == 3) {
                // inner-sub A <= Li < Ri <= B
                L = rnd.next(A, B - 1);
                R = rnd.next(L + 1, B);
            } else if (kind == 4) {
                // disjoint-left Ri < A
                int Rmax = A - 1;
                int Rmin = 1;
                if (Rmin > Rmax) Rmin = Rmax; // safety, though should not happen
                R = rnd.next(Rmin, Rmax);
                L = rnd.next(0, R - 1);
            } else { // kind == 5
                // disjoint-right Li > B
                int Lmin = B + 1;
                int Lmax = C - 1;
                if (Lmin > Lmax) Lmin = Lmax; // safety
                L = rnd.next(Lmin, Lmax);
                R = rnd.next(L + 1, C);
            }
            segs.push_back({L, R});
        }
        K = computeSum(A, B, segs); // guaranteed > 0

    } else if (scenario == 2) {
        // Scenario 2: Small coordinates, guaranteed NO solution (K not attainable).
        int C = rnd.next(5, 25);
        N = rnd.next(2, 8);
        segs.clear();
        for (int i = 0; i < N; i++) {
            int L = rnd.next(0, C - 1);
            int R = rnd.next(L + 1, C);
            segs.push_back({L, R});
        }

        // Enumerate all sums S(A,B) for 0 <= A < B <= C
        set<long long> vals;
        long long maxS = 0;
        for (int A = 0; A <= C; A++) {
            for (int B = A + 1; B <= C; B++) {
                long long s = computeSum(A, B, segs);
                vals.insert(s);
                if (s > maxS) maxS = s;
            }
        }

        // Choose K not in vals and >= 1.
        // maxS is the maximum possible; so maxS + 1 is safe and > 0.
        K = maxS + 1;
        if (K < 1) K = 1; // extremely unlikely to have maxS < 0

    } else if (scenario == 3) {
        // Scenario 3: Large coordinates (up to 1e6), guaranteed solution.
        const int MAXC = 1000000;
        int len = rnd.next(1, 1000);
        int A = rnd.next(0, MAXC - len);
        int B = A + len;

        N = rnd.next(5, 15);
        segs.clear();

        // First interval exactly [A,B] to ensure overlap.
        segs.push_back({A, B});

        // Remaining intervals random across full range.
        for (int i = 1; i < N; i++) {
            int L = rnd.next(0, MAXC - 1);
            int R = rnd.next(L + 1, MAXC);
            segs.push_back({L, R});
        }

        K = computeSum(A, B, segs); // >= B-A >= 1

    } else {
        // Scenario 4: Small coordinates, random intervals, K chosen from some (A,B) with S>0.
        int C = rnd.next(5, 25);
        N = rnd.next(2, 10);
        segs.clear();
        for (int i = 0; i < N; i++) {
            int L = rnd.next(0, C - 1);
            int R = rnd.next(L + 1, C);
            segs.push_back({L, R});
        }

        vector<pair<pair<int,int>, long long>> candidates;
        for (int A = 0; A <= C; A++) {
            for (int B = A + 1; B <= C; B++) {
                long long s = computeSum(A, B, segs);
                if (s > 0) candidates.push_back({{A, B}, s});
            }
        }

        if (candidates.empty()) {
            // Extremely unlikely, but to be safe, fall back to simple constructed one.
            int L = 0, R = C;
            segs.clear();
            segs.push_back({L, R});
            N = 1;
            int A = rnd.next(L, R - 1);
            int B = rnd.next(A + 1, R);
            K = computeSum(A, B, segs);
        } else {
            auto chosen = rnd.any(candidates);
            K = chosen.second;
        }
    }

    // Ensure constraints: 1 <= N <= 1000, 1 <= K <= 1e9, 0 <= coords <= 1e6.
    // Our construction respects tighter bounds.

    println(N, K);
    for (auto &pr : segs) {
        println(pr.first, pr.second);
    }

    return 0;
}
