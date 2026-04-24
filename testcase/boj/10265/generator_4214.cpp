#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // small number of people
    int n = rnd.next(1, 10);

    // prepare a shuffled list of nodes 1..n
    vector<int> nodes(n);
    for (int i = 0; i < n; i++) nodes[i] = i + 1;
    shuffle(nodes.begin(), nodes.end());

    // decide how many disjoint cycles to seed (1 to min(n,3))
    int c = rnd.next(1, min(n, 3));
    vector<int> x(n + 1, 1);
    int rem = n, pos = 0;

    // build c cycles consuming all nodes
    for (int i = 0; i < c; i++) {
        int minLeft = c - i - 1; // at least one node for each remaining cycle
        int sz = (i + 1 == c ? rem : rnd.next(1, rem - minLeft));
        vector<int> cyc(nodes.begin() + pos, nodes.begin() + pos + sz);
        shuffle(cyc.begin(), cyc.end());
        for (int j = 0; j < sz; j++) {
            int u = cyc[j], v = cyc[(j + 1) % sz];
            x[u] = v;
        }
        pos += sz;
        rem -= sz;
    }

    // for any leftover nodes, attach randomly or self-point
    for (int i = pos; i < n; i++) {
        int u = nodes[i];
        if (rnd.next() < 0.3)
            x[u] = u;
        else
            x[u] = rnd.next(1, n);
    }

    // choose k in varied segments: tiny up to full
    int a = max(1, n / 5);
    int b = max(1, 2 * n / 5);
    int c2 = max(1, 3 * n / 5);
    int d = max(1, 4 * n / 5);
    int seg = rnd.next(0, 4);
    int L, R;
    if (seg == 0) { L = 1;      R = a; }
    else if (seg == 1) { L = a+1;  R = b; }
    else if (seg == 2) { L = b+1;  R = c2; }
    else if (seg == 3) { L = c2+1; R = d; }
    else { L = d+1;    R = n; }
    if (L > R) { L = 1; R = n; }
    int k = rnd.next(L, R);

    // output the test case
    println(n, k);
    vector<int> xi(n);
    for (int i = 1; i <= n; i++) xi[i-1] = x[i];
    println(xi);

    return 0;
}
