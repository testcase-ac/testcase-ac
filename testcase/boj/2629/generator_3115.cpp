#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of weights
    int N = rnd.next(1, 10);

    // Hyper-parameter: maximum individual weight
    int Wmax = rnd.next(5, 20);

    // Bias for distribution: negative => small weights, positive => large weights
    vector<int> biases = {-2, -1, 0, 1, 2};
    int bias = rnd.any(biases);

    // Generate weights with possible duplicates, biased
    vector<int> w(N);
    for (int i = 0; i < N; i++) {
        w[i] = rnd.wnext(Wmax, bias) + 1; // in [1..Wmax]
    }
    sort(w.begin(), w.end());

    // Compute total sum of weights
    int sumW = accumulate(w.begin(), w.end(), 0);

    // Compute all reachable weight differences via DFS
    vector<bool> reachable(sumW + 1, false);
    function<void(int,int)> dfs = [&](int idx, int diff) {
        if (idx == N) {
            int d = abs(diff);
            if (d <= sumW) reachable[d] = true;
            return;
        }
        // put w[idx] on left pan
        dfs(idx + 1, diff + w[idx]);
        // put w[idx] on right pan
        dfs(idx + 1, diff - w[idx]);
        // do not use w[idx]
        dfs(idx + 1, diff);
    };
    dfs(0, 0);

    // Decide a maximum marble weight to consider
    int maxRange = sumW + rnd.next(1, Wmax);

    // Build lists of reachable and unreachable marble weights
    vector<int> reachList, unreachList;
    for (int x = 1; x <= maxRange; x++) {
        bool can = (x <= sumW && reachable[x]);
        if (can) reachList.push_back(x);
        else unreachList.push_back(x);
    }
    // Guarantee at least one unreachable
    if (unreachList.empty()) {
        unreachList.push_back(sumW + 1);
    }
    // Guarantee at least one reachable if possible
    if (reachList.empty()) {
        // put smallest weight itself
        reachList.push_back(w[0]);
    }

    // Number of marbles
    int M = rnd.next(1, 7);
    vector<int> marbles;
    // Ensure diversity: at least one reachable and one unreachable if M>=2
    if (M >= 1) {
        marbles.push_back(rnd.any(reachList));
    }
    if (M >= 2) {
        marbles.push_back(rnd.any(unreachList));
    }
    // Fill the rest randomly
    for (int i = marbles.size(); i < M; i++) {
        if (rnd.next(0,1) == 0) {
            marbles.push_back(rnd.any(reachList));
        } else {
            marbles.push_back(rnd.any(unreachList));
        }
    }
    // Shuffle the marble queries
    shuffle(marbles.begin(), marbles.end());

    // Output in required format
    println(N);
    println(w);
    println(M);
    println(marbles);

    return 0;
}
