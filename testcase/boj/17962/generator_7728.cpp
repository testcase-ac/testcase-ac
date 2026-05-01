#include "testlib.h"
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of nodes between 1 and 12 for hand-checkable sizes
    int n = rnd.next(1, 12);
    println(n);
    if (n == 1) return 0;

    // Choose tree shape: 0=path, 1=star, 2=complete binary, 3=caterpillar
    int type = rnd.next(0, 3);
    vector<pair<int,int>> edges;
    if (type == 0) {
        // path: 1-2-3-...-n
        for (int i = 2; i <= n; ++i)
            edges.emplace_back(i - 1, i);
    } else if (type == 1) {
        // star centered at 1
        for (int i = 2; i <= n; ++i)
            edges.emplace_back(1, i);
    } else if (type == 2) {
        // complete binary tree
        for (int i = 2; i <= n; ++i)
            edges.emplace_back(i / 2, i);
    } else {
        // caterpillar: a spine of length s, others attach to spine
        int s = rnd.next(1, n - 1);
        for (int i = 2; i <= s; ++i)
            edges.emplace_back(i - 1, i);
        for (int i = s + 1; i <= n; ++i)
            edges.emplace_back(rnd.next(1, s), i);
    }

    // randomize edge order
    shuffle(edges.begin(), edges.end());
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
