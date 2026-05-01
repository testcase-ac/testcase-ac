#include "testlib.h"
using namespace std;

void genRandom(int densKind, int prefKind, int &N, int &R, string &curr, string &pref, vector<pair<int,int>> &edges) {
    // N selection (kept small for readability and char limit)
    if (densKind == 0)
        N = rnd.next(1, 7);
    else if (densKind == 1)
        N = rnd.next(4, 12);
    else
        N = rnd.next(8, 15);

    // Generate current teams string
    int pattern = rnd.next(0, 3); // 0: all A, 1: all B, 2: alternating, 3: random
    curr.assign(N, 'A');
    if (pattern == 0) {
        for (int i = 0; i < N; ++i) curr[i] = 'A';
    } else if (pattern == 1) {
        for (int i = 0; i < N; ++i) curr[i] = 'B';
    } else if (pattern == 2) {
        for (int i = 0; i < N; ++i) curr[i] = (i % 2 == 0 ? 'A' : 'B');
    } else {
        for (int i = 0; i < N; ++i) curr[i] = (rnd.next(0, 1) == 0 ? 'A' : 'B');
    }

    // Generate preference string
    pref.assign(N, '?');
    if (prefKind == 0) {
        // Many '?'
        for (int i = 0; i < N; ++i) {
            int r = rnd.next(0, 99);
            if (r < 70) pref[i] = '?';
            else pref[i] = (rnd.next(0, 1) == 0 ? 'A' : 'B');
        }
    } else if (prefKind == 1) {
        // Medium '?', partly correlated with current team
        for (int i = 0; i < N; ++i) {
            int r = rnd.next(0, 99);
            if (r < 30) pref[i] = '?';
            else if (r < 65) pref[i] = curr[i];
            else pref[i] = (curr[i] == 'A' ? 'B' : 'A');
        }
    } else {
        // Few '?', many forced A/B
        for (int i = 0; i < N; ++i) {
            int r = rnd.next(0, 99);
            if (r < 10) pref[i] = '?';
            else pref[i] = (rnd.next(0, 1) == 0 ? 'A' : 'B');
        }
    }

    // Generate rivalries, only between opposite current teams (keeps graph bipartite)
    edges.clear();
    vector<pair<int,int>> cand;
    for (int i = 1; i <= N; ++i)
        for (int j = i + 1; j <= N; ++j)
            if (curr[i - 1] != curr[j - 1])
                cand.emplace_back(i, j);

    int total = (int)cand.size();
    if (total == 0) {
        R = 0;
        return;
    }

    shuffle(cand.begin(), cand.end());

    if (densKind == 0) {
        // Sparse
        int maxR = min(total, max(0, N - 1));
        if (maxR == 0) R = 0;
        else R = rnd.next(0, maxR);
    } else if (densKind == 1) {
        // Medium density
        int ratio = rnd.next(25, 60); // percent
        R = total * ratio / 100;
        if (R == 0) R = 1;
        if (R > total) R = total;
    } else {
        // Dense
        int ratio = rnd.next(70, 100); // percent
        R = total * ratio / 100;
        if (R == 0) R = 1;
        if (R > total) R = total;
    }

    edges.assign(cand.begin(), cand.begin() + R);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 5);

    int N = 0, R = 0;
    string curr, pref;
    vector<pair<int,int>> edges;

    if (scenario == 0) {
        // Very small, no rivalries: tests handling of only preference constraints
        N = rnd.next(1, 5);
        curr.assign(N, 'A');
        for (int i = 0; i < N; ++i)
            curr[i] = (rnd.next(0, 1) == 0 ? 'A' : 'B');

        pref.assign(N, '?');
        for (int i = 0; i < N; ++i) {
            int r = rnd.next(0, 99);
            if (r < 33) pref[i] = '?';
            else if (r < 66) pref[i] = 'A';
            else pref[i] = 'B';
        }

        R = 0;
        edges.clear();
    } else if (scenario == 1) {
        // Example 1 from statement
        N = 5;
        curr = "AAABB";
        pref = "??AAA";
        edges.clear();
        edges.emplace_back(1, 4);
        edges.emplace_back(2, 4);
        edges.emplace_back(3, 4);
        edges.emplace_back(3, 5);
        R = (int)edges.size();
    } else if (scenario == 2) {
        // Example 2 from statement
        N = 2;
        curr = "AB";
        pref = "AA";
        edges.clear();
        edges.emplace_back(1, 2);
        R = (int)edges.size();
    } else if (scenario == 3) {
        // Example 3 from statement
        N = 8;
        curr = "ABBABAAA";
        pref = "?B?ABBAB";
        edges.clear();
        edges.emplace_back(1, 2);
        edges.emplace_back(4, 3);
        edges.emplace_back(6, 5);
        edges.emplace_back(4, 5);
        edges.emplace_back(1, 5);
        edges.emplace_back(2, 8);
        edges.emplace_back(3, 7);
        edges.emplace_back(2, 4);
        R = (int)edges.size();
    } else if (scenario == 4) {
        // Random, sparse to medium density, varied preferences
        int densKind = rnd.next(0, 1);   // 0 or 1
        int prefKind = rnd.next(0, 2);   // 0,1,2
        genRandom(densKind, prefKind, N, R, curr, pref, edges);
        R = (int)edges.size();
    } else {
        // Random, typically denser graph, harsher preferences
        int densKind = 2;
        int prefKind = rnd.next(1, 2);   // 1 or 2
        genRandom(densKind, prefKind, N, R, curr, pref, edges);
        R = (int)edges.size();
    }

    println(N, R);
    println(curr);
    println(pref);
    for (const auto &e : edges)
        println(e.first, e.second);

    return 0;
}
