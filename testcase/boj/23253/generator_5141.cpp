#include "testlib.h"
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes
    int N = rnd.next(2, 10);
    bool wantSolvable = rnd.next(0, 1);

    // Choose M: if we want unsolvable, force M < N so a violation is possible
    int M;
    if (wantSolvable) {
        M = rnd.next(1, N);
    } else {
        M = rnd.next(1, max(1, N - 1));
    }

    // Partition N into M positive sizes
    vector<int> sizes(M, 1);
    int rem = N - M;
    for (int i = 0; i < rem; i++) {
        int idx = rnd.next(0, M - 1);
        sizes[idx]++;
    }

    // Prepare stacks
    vector<vector<int>> stacks(M);

    if (wantSolvable) {
        // Solvable: random partition then sort each stack so top-down is 1..N
        vector<int> avail(N);
        iota(avail.begin(), avail.end(), 1);
        shuffle(avail.begin(), avail.end());
        int pos = 0;
        for (int i = 0; i < M; i++) {
            stacks[i].assign(avail.begin() + pos, avail.begin() + pos + sizes[i]);
            pos += sizes[i];
            // Descending bottom-to-top so top is smallest
            sort(stacks[i].begin(), stacks[i].end(), greater<int>());
        }
    } else {
        // Unsolvable: force a violation for some a and a+1 in one stack
        int a = rnd.next(1, N - 1);
        // Build avail2 = all except a, a+1
        vector<int> avail2;
        avail2.reserve(N - 2);
        for (int x = 1; x <= N; x++) {
            if (x != a && x != a + 1) avail2.push_back(x);
        }
        shuffle(avail2.begin(), avail2.end());
        // Pick a stack with size >= 2
        vector<int> good;
        for (int i = 0; i < M; i++) {
            if (sizes[i] >= 2) good.push_back(i);
        }
        int s = rnd.any(good);
        // Fill stack s: place a below a+1, plus other random elements
        int sz_s = sizes[s];
        int other_sz = sz_s - 2;
        int p2 = 0;
        vector<int> others_s(avail2.begin(), avail2.begin() + other_sz);
        p2 += other_sz;
        shuffle(others_s.begin(), others_s.end());
        int pos_a = rnd.next(0, sz_s - 2);
        int pos_ap = rnd.next(pos_a + 1, sz_s - 1);
        stacks[s].assign(sz_s, 0);
        int idx_o = 0;
        for (int pos = 0; pos < sz_s; pos++) {
            if (pos == pos_a) stacks[s][pos] = a;
            else if (pos == pos_ap) stacks[s][pos] = a + 1;
            else {
                stacks[s][pos] = others_s[idx_o++];
            }
        }
        // Fill other stacks with remaining numbers
        for (int i = 0; i < M; i++) {
            if (i == s) continue;
            int sz = sizes[i];
            stacks[i].assign(avail2.begin() + p2, avail2.begin() + p2 + sz);
            shuffle(stacks[i].begin(), stacks[i].end());
            p2 += sz;
        }
    }

    // Output
    println(N, M);
    for (int i = 0; i < M; i++) {
        println((int)stacks[i].size());
        println(stacks[i]);
    }
    return 0;
}
