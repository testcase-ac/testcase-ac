#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of logs
    int N = rnd.next(5, 12);
    // Number of components (clusters)
    int maxComp = min(4, N/2);
    int K = rnd.next(2, maxComp);
    // Distribute sizes among components
    vector<int> compSize(K, 1);
    for (int i = 0; i < N - K; i++) {
        compSize[rnd.next(0, K-1)]++;
    }
    // Prepare logs: each entry is ((x1,x2), y), y will be filled later
    vector<pair<pair<int,int>, int>> logs;
    logs.reserve(N);
    // Track which log belongs to which component
    vector<vector<int>> compLogs(K);
    int idx = 0;
    for (int c = 0; c < K; c++) {
        int s = compSize[c];
        int offset = c * 100; // separate x-ranges
        // First log in component
        int prev_l = rnd.next(0, 5);
        int prev_len = rnd.next(1, 5);
        int l = offset + prev_l;
        int r = l + prev_len;
        logs.push_back({{l, r}, 0});
        compLogs[c].push_back(idx++);
        // Chain the rest so each overlaps its predecessor
        for (int i = 1; i < s; i++) {
            int delta = 0;
            if (prev_len > 1) delta = rnd.next(1, prev_len - 1);
            int cur_l = prev_l + delta;
            int cur_len = rnd.next(1, 5);
            int cur_r = cur_l + cur_len;
            l = offset + cur_l;
            r = offset + cur_r;
            logs.push_back({{l, r}, 0});
            compLogs[c].push_back(idx++);
            // update for next
            prev_l = cur_l;
            prev_len = cur_len;
        }
    }
    // Assign random distinct y-coordinates
    vector<int> Y(N);
    for (int i = 0; i < N; i++) {
        Y[i] = i * 10 + rnd.next(1, 9);
    }
    shuffle(Y.begin(), Y.end());
    for (int i = 0; i < N; i++) {
        logs[i].second = Y[i];
    }
    // Queries count
    int Q = rnd.next(N, 2 * N);
    // Prepare queries: some yes, some no
    int yesQ = rnd.next(1, Q-1);
    int noQ = Q - yesQ;
    vector<pair<int,int>> queries;
    queries.reserve(Q);
    // Yes queries: pick pairs within same component
    vector<int> compsWithTwo;
    for (int c = 0; c < K; c++) {
        if ((int)compLogs[c].size() >= 2) compsWithTwo.push_back(c);
    }
    for (int i = 0; i < yesQ; i++) {
        int c = rnd.any(compsWithTwo);
        auto &v = compLogs[c];
        int a = rnd.next(0, (int)v.size() - 1);
        int b = rnd.next(0, (int)v.size() - 1);
        while (b == a) b = rnd.next(0, (int)v.size() - 1);
        queries.emplace_back(v[a] + 1, v[b] + 1);
    }
    // No queries: pick from different components
    for (int i = 0; i < noQ; i++) {
        int c1 = rnd.next(0, K-1), c2 = rnd.next(0, K-1);
        while (c2 == c1) c2 = rnd.next(0, K-1);
        int a = rnd.any(compLogs[c1]);
        int b = rnd.any(compLogs[c2]);
        queries.emplace_back(a + 1, b + 1);
    }
    // Output
    println(N, Q);
    for (int i = 0; i < N; i++) {
        println(logs[i].first.first, logs[i].first.second, logs[i].second);
    }
    for (auto &q : queries) {
        println(q.first, q.second);
    }
    return 0;
}
