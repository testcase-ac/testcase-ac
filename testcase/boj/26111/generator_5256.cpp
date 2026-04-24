#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of nodes (rooted tree of size N)
    int N = rnd.next(1, 10);
    // Bias parameter: >0 favors deep (chain-like), <0 favors shallow (star-like), 0 uniform
    int bias = rnd.next(-2, 2);

    // Build a random rooted ordered tree on nodes [0..N-1]
    vector<vector<int>> children(N);
    for (int i = 1; i < N; i++) {
        // parent in [0..i-1], weighted by bias
        int p = rnd.wnext(i, bias);
        children[p].push_back(i);
    }

    // Randomly decide to shuffle the order of children for diversity
    double shuffleProb = rnd.next(); // [0,1)
    if (rnd.next() < shuffleProb) {
        for (int u = 0; u < N; u++) {
            shuffle(children[u].begin(), children[u].end());
        }
    }

    // Build the parentheses representation via DFS
    function<string(int)> build = [&](int u) {
        string s = "(";
        for (int v : children[u]) {
            s += build(v);
        }
        s += ")";
        return s;
    };

    string ans = build(0);
    // Output the parentheses string
    printf("%s\n", ans.c_str());

    return 0;
}
