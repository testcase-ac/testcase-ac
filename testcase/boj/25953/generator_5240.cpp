#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for diversity
    int n = rnd.next(2, 10);
    int t = rnd.next(1, 5);
    int maxEdges = n * (n - 1) / 2;
    int m_upper = min(maxEdges, 10);
    vector<int> skewOpts = {-1, 0, 1};
    int skew_m = rnd.any(skewOpts);
    int m0 = rnd.wnext(m_upper + 1, skew_m);
    int m = max(1, min(m0, m_upper));
    int skew_w = rnd.any(skewOpts);
    int w_upper = rnd.wnext(10, skew_w) + 1;  // weights in [1, w_upper]

    // Choose distinct start and end
    int s = rnd.next(0, n - 1);
    int e = rnd.next(0, n - 2);
    if (e >= s) e++;

    // Prepare all possible undirected edges
    vector<pair<int,int>> allEdges;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            allEdges.emplace_back(i, j);

    // Output header
    println(n, t, m);
    println(s, e);

    // For each time, pick m distinct edges and random weights
    for (int ti = 1; ti <= t; ti++) {
        shuffle(allEdges.begin(), allEdges.end());
        for (int i = 0; i < m; i++) {
            auto ed = allEdges[i];
            int w = rnd.next(1, w_upper);
            println(ed.first, ed.second, w);
        }
    }
    return 0;
}
