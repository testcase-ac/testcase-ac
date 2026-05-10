#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const int MAXH = 100000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    vector<int> h = inf.readInts(N, 1, MAXH, "h_i");
    inf.readEoln();

    // Now validate the global property: for every building, the problem's
    // definition implies we can determine:
    //  - how many buildings it can see
    //  - among the nearest visible buildings, the smallest index.
    //
    // We will simulate the visibility according to the statement to ensure
    // there is no hidden impossible input structure. This does not affect
    // complexity (O(N) or O(N log N)).

    // For each building i, compute:
    //   cnt[i]: total visible buildings
    //   bestIdx[i]: smallest index among nearest visible buildings
    //
    // Visibility rule interpreted from statement and examples:
    //   From building i (height H = h[i]), in one direction, we scan outward.
    //   A building j in that direction is visible if:
    //     - h[j] > H (strictly higher than current building)
    //     - and there is no building k between i and j with h[k] >= h[j]
    //   (i.e., the typical "see higher skyline" monotone-stack visibility).
    //
    // We'll do it in both directions using a stack for efficiency.

    int n = N;
    vector<int> cntLeft(n, 0), cntRight(n, 0);
    vector<int> nearestLeftDist(n, INT_MAX), nearestRightDist(n, INT_MAX);
    vector<int> nearestLeftIdx(n, -1), nearestRightIdx(n, -1);

    // Left side visibility
    {
        // Stack holds indices of buildings that are "candidates" to be seen
        // when looking from the right to the left. We process from left to right
        // but we need, for each i, all visible to the left, so process i from 0..n-1
        // with a monotone decreasing stack by height.
        vector<int> st;
        st.reserve(n);
        for (int i = 0; i < n; ++i) {
            int H = h[i];
            // For building i, visible to left are exactly the elements in stack
            // that are strictly higher than H, but with blocking handled by stack invariants.
            // Standard "see taller" logic: pop while stack top <= H.
            while (!st.empty() && h[st.back()] <= H) st.pop_back();
            // Now, all remaining in stack are visible to i (for counting),
            // but they might be multiple. However, canonical approach: every time
            // we push i, i becomes visible to any future building with smaller height.
            // To count correctly for each i, we need a different method:
            // Instead, we can compute visibility counts by scanning from i outward,
            // but that would be O(N^2). The problem statement does not actually
            // force us to compute exact counts in validator, only to ensure
            // problem assumptions like "answer always exists" are consistent.
            //
            // Therefore, we *do not* need exact visibility counts here.
            // We only need to ensure that from any i, we can at least determine
            // some valid (possibly 0) visible set. The geometrical setting
            // (finite line of positive heights) trivially guarantees this:
            // visibility definition never contradicts itself.
            //
            // So we don't need to do expensive or complex checks here.
            //
            // We'll just compute the *nearest* higher building on each side,
            // which is easy and guaranteed to exist or not; no contradiction.
            //
            // => Break here and compute nearest-higher separately below.
        }
    }

    // Compute nearest higher building to the left and right (for each i),
    // then check that there is no logical inconsistency. This also
    // mirrors what many intended solutions do.

    // Nearest higher to the left
    {
        vector<int> st;
        st.reserve(n);
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && h[st.back()] <= h[i]) st.pop_back();
            if (!st.empty()) {
                int j = st.back();
                int dist = i - j;
                nearestLeftDist[i] = dist;
                nearestLeftIdx[i] = j;
            }
            st.push_back(i);
        }
    }
    // Nearest higher to the right
    {
        vector<int> st;
        st.reserve(n);
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && h[st.back()] <= h[i]) st.pop_back();
            if (!st.empty()) {
                int j = st.back();
                int dist = j - i;
                nearestRightDist[i] = dist;
                nearestRightIdx[i] = j;
            }
            st.push_back(i);
        }
    }

    // For each i, it's always valid that:
    //  - visible count >= number of nearest-higher found (0, 1 or 2).
    //  - if none found, count can be 0.
    // There is no contradictory configuration possible, so no need
    // for extra ensuref about "answer always exists"; it's trivially true.

    // Still, we can sanity-check: distances and indices must be consistent.
    for (int i = 0; i < n; ++i) {
        if (nearestLeftIdx[i] != -1) {
            int j = nearestLeftIdx[i];
            int dist = nearestLeftDist[i];
            ensuref(j >= 0 && j < n, "nearestLeftIdx out of range at i=%d", i+1);
            ensuref(j < i, "nearestLeftIdx must be to the left at i=%d", i+1);
            ensuref(dist == i - j && dist > 0, "invalid nearestLeftDist at i=%d", i+1);
            ensuref(h[j] > h[i], "nearestLeft must be higher at i=%d", i+1);
        }
        if (nearestRightIdx[i] != -1) {
            int j = nearestRightIdx[i];
            int dist = nearestRightDist[i];
            ensuref(j >= 0 && j < n, "nearestRightIdx out of range at i=%d", i+1);
            ensuref(j > i, "nearestRightIdx must be to the right at i=%d", i+1);
            ensuref(dist == j - i && dist > 0, "invalid nearestRightDist at i=%d", i+1);
            ensuref(h[j] > h[i], "nearestRight must be higher at i=%d", i+1);
        }
    }

    inf.readEof();
}
