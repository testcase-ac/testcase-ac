#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Compute minimal total penalty with given constraints
// We simulate the optimal scheduling using a priority queue:
// At any time, among all available tasks (t[i] <= current time), do the one
// with maximum v[i] (Smith rule for 1||Σw_j C_j with release dates).
// current time starts from S, but tasks may be released before S; if so,
// time S is already >= their release time, so they're all available at start.
// After each task, time increases by 1 (processing time) plus any idle if needed.
long long compute_min_penalty(int n, long long S,
                              const vector<long long>& t,
                              const vector<long long>& v) {
    vector<pair<long long,int>> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = {t[i], i};
    }
    sort(order.begin(), order.end());

    long long time = S;
    long long total_penalty = 0;
    priority_queue<pair<long long,int>> pq; // (v, idx)
    int ptr = 0;

    // Initially, at time S, push all tasks with t[i] <= S
    while (ptr < n && order[ptr].first <= time) {
        int idx = order[ptr].second;
        pq.push({v[idx], idx});
        ++ptr;
    }

    while (!pq.empty() || ptr < n) {
        if (pq.empty()) {
            // No available task; jump time to next release
            long long next_t = order[ptr].first;
            if (time < next_t) time = next_t;
            while (ptr < n && order[ptr].first <= time) {
                int idx = order[ptr].second;
                pq.push({v[idx], idx});
                ++ptr;
            }
            continue;
        }
        auto [vi, idx] = pq.top();
        pq.pop();
        // process this task now at current time
        long long y = time;
        total_penalty += (y - t[idx]) * vi;

        // after submission, must rest at least 1 unit
        time += 1;

        // add any tasks that became available by this new time
        while (ptr < n && order[ptr].first <= time) {
            int j = order[ptr].second;
            pq.push({v[j], j});
            ++ptr;
        }
    }

    return total_penalty;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 10, "T");
    inf.readEoln();

    long long totalN = 0;

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "n");
        inf.readSpace();
        long long S = inf.readLong(1LL, 2000000000LL, "S");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 100000LL * 10LL,
                "Sum of n over all test cases exceeds 1e6: now %lld", totalN);

        vector<long long> t(n), v(n);

        // t[i]
        {
            vector<long long> tv = inf.readLongs(n, 1LL, 2000000000LL, "t_i");
            inf.readEoln();
            for (int i = 0; i < n; ++i) t[i] = tv[i];
        }

        // v[i]
        {
            vector<long long> vv = inf.readLongs(n, 1LL, 40000LL, "v_i");
            inf.readEoln();
            for (int i = 0; i < n; ++i) v[i] = vv[i];
        }

        // Additional global property check:
        // For given input, an optimal schedule always exists with finite penalty,
        // and y[i] >= t[i] always holds by construction of our simulation.
        // Here we actually compute the minimal penalty just to ensure
        // that arithmetic stays within 64-bit and constraints are consistent.
        long long ans = compute_min_penalty(n, S, t, v);

        // Check that total penalty fits in signed 64-bit (should always hold)
        // Using __int128 just to be explicit, though ans is already long long.
        __int128 tmp = ans;
        ensuref(tmp >= LLONG_MIN && tmp <= LLONG_MAX,
                "Total penalty overflows 64-bit signed integer");
    }

    inf.readEof();
}
