#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N (prefer small, sometimes minimal)
    int maxN = 20;
    int N;
    if (rnd.next(0, 9) == 0) {
        N = 1;
    } else {
        N = rnd.next(2, maxN);
    }

    vector<int> h(N);

    // Choose a pattern type for heights
    int patternTypes = 6;
    int type = rnd.next(0, patternTypes - 1);

    if (type == 0) {
        // Completely random small-ish heights
        for (int i = 0; i < N; ++i)
            h[i] = rnd.next(1, 20);
    } else if (type == 1) {
        // Strictly increasing
        int start = rnd.next(1, 10);
        int step = rnd.next(1, 5);
        for (int i = 0; i < N; ++i)
            h[i] = start + step * i;
    } else if (type == 2) {
        // Strictly decreasing
        int step = rnd.next(1, 5);
        int peak = rnd.next(1, 10) + step * (N - 1);
        for (int i = 0; i < N; ++i)
            h[i] = peak - step * i;
    } else if (type == 3 && N >= 3) {
        // Valley: high -> low -> high
        int pivot = rnd.next(1, N - 2); // 1 .. N-2
        int mid = rnd.next(1, 10);
        int stepL = rnd.next(1, 5);
        int stepR = rnd.next(1, 5);
        h[pivot] = mid;
        for (int i = pivot - 1; i >= 0; --i)
            h[i] = h[i + 1] + stepL;
        for (int i = pivot + 1; i < N; ++i)
            h[i] = h[i - 1] + stepR;
    } else if (type == 4 && N >= 3) {
        // Mountain: low -> high -> low (not necessarily strictly)
        int pivot = rnd.next(1, N - 2); // 1 .. N-2
        int base = rnd.next(5, 15);
        int upStep = rnd.next(1, 3);
        int downStep = rnd.next(1, 3);
        for (int i = 0; i <= pivot; ++i)
            h[i] = base + upStep * i;
        for (int i = pivot + 1; i < N; ++i) {
            int val = base + upStep * pivot - downStep * (i - pivot);
            if (val < 1) val = 1;
            h[i] = val;
        }
    } else {
        // Few distinct values (includes constant array case)
        int K = rnd.next(1, min(4, N));
        vector<int> vals;
        while ((int)vals.size() < K) {
            int v = rnd.next(1, 20);
            bool ok = true;
            for (int x : vals)
                if (x == v) { ok = false; break; }
            if (ok) vals.push_back(v);
        }
        for (int i = 0; i < N; ++i)
            h[i] = rnd.any(vals);
    }

    // Inject some extreme values sometimes to test large/small behavior
    if (N >= 1 && rnd.next(0, 2) == 0) {
        int idx = rnd.next(0, N - 1);
        h[idx] = 1;
    }
    if (N >= 1 && rnd.next(0, 2) == 0) {
        int idx = rnd.next(0, N - 1);
        h[idx] = rnd.next(1000000000 - 100, 1000000000);
    }

    // Build queries
    vector<tuple<int,int,int>> queries;

    auto addQuery = [&](int l, int r, int w) {
        queries.emplace_back(l, r, w);
    };

    if (N == 1) {
        // Only possible query windows
        addQuery(1, 1, 1);
    } else {
        // Some structured queries on full range
        addQuery(1, N, 1);      // width 1 over whole
        addQuery(1, N, N);      // whole range as one window
        if (N >= 2) addQuery(1, N, 2);
        if (N >= 3) addQuery(1, N, N - 1);

        // One random range query
        int l = rnd.next(1, N);
        int r = rnd.next(l, N);
        int len = r - l + 1;
        int w;
        int mode = rnd.next(0, 2);
        if (mode == 0) w = 1;
        else if (mode == 1) w = len;
        else w = rnd.next(1, len);
        addQuery(l, r, w);

        // Sometimes a single-bar query
        if (rnd.next(0, 1) == 0) {
            int pos = rnd.next(1, N);
            addQuery(pos, pos, 1);
        }
    }

    int maxQ = 25;
    int minQ = 5;
    if (N == 1) minQ = 1;

    int cur = (int)queries.size();
    int targetQ = rnd.next(max(cur, minQ), maxQ);

    while ((int)queries.size() < targetQ) {
        int l = rnd.next(1, N);
        int r = rnd.next(l, N);
        int len = r - l + 1;
        int w;
        int mode = rnd.next(0, 2);
        if (mode == 0) w = 1;
        else if (mode == 1) w = len;
        else w = rnd.next(1, len);
        addQuery(l, r, w);
    }

    // Shuffle queries to avoid predictable order
    shuffle(queries.begin(), queries.end());

    // Output
    println(N);
    println(h);

    int Q = (int)queries.size();
    println(Q);
    for (size_t i = 0; i < queries.size(); ++i) {
        int l, r, w;
        tie(l, r, w) = queries[i];
        println(l, r, w);
    }

    return 0;
}
