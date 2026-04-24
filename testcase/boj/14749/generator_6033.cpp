#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose n with varied distribution: small, medium, larger
    int rr = rnd.next(100);  // [0,99]
    int n;
    if (rr < 20) {
        n = rnd.next(2, 4);
    } else if (rr < 60) {
        n = rnd.next(5, 10);
    } else {
        n = rnd.next(11, 15);
    }

    // Choose tree shape: 0=path, 1=star, 2=random attach, 3=caterpillar (only if n>=3)
    int shape;
    if (n <= 2) {
        shape = rnd.next(0, 2);
    } else {
        shape = rnd.next(0, 3);
    }

    vector<pair<int,int>> edges;
    if (shape == 0) {
        // path
        for (int i = 2; i <= n; i++)
            edges.emplace_back(i - 1, i);
    } else if (shape == 1) {
        // star centered at 1
        for (int i = 2; i <= n; i++)
            edges.emplace_back(1, i);
    } else if (shape == 2) {
        // random tree by attaching each new node to a previous one
        for (int i = 2; i <= n; i++) {
            int p = rnd.next(1, i - 1);
            edges.emplace_back(p, i);
        }
    } else {
        // caterpillar: a spine plus leaves
        int k = rnd.next(2, n - 1);  // length of spine
        for (int i = 2; i <= k; i++)
            edges.emplace_back(i - 1, i);
        for (int i = k + 1; i <= n; i++) {
            int p = rnd.next(1, k);
            edges.emplace_back(p, i);
        }
    }

    // Shuffle edge listing
    shuffle(edges.begin(), edges.end());

    // Choose distinct start and end
    int s = rnd.next(1, n);
    int t = rnd.next(1, n);
    while (t == s) t = rnd.next(1, n);

    // Output
    println(n);
    for (auto &e : edges)
        println(e.first, e.second);
    println(s, t);

    return 0;
}
