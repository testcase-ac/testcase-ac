#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, rnd.next(0, 9) == 0 ? 80 : 20);
    vector<int> a(n + 1, n);

    if (n == 1) {
        println(1);
        println(1);
        return 0;
    }

    vector<int> nodes(n - 1);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());

    if (mode == 0) {
        for (int i = 0; i + 1 < (int)nodes.size(); ++i) {
            a[nodes[i]] = nodes[i + 1];
        }
        a[nodes.back()] = n;
    } else if (mode == 1) {
        int cycleLen = rnd.next(1, n - 1);
        vector<int> cycle(nodes.begin(), nodes.begin() + cycleLen);
        for (int i = 0; i < cycleLen; ++i) {
            a[cycle[i]] = cycle[(i + 1) % cycleLen];
        }
        for (int i = cycleLen; i < n - 1; ++i) {
            a[nodes[i]] = rnd.next(0, 1) ? n : nodes[rnd.next(0, i - 1)];
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            a[i] = rnd.next(1, n);
        }
    } else if (mode == 3) {
        int hub = rnd.any(nodes);
        for (int v : nodes) {
            int choice = rnd.next(0, 3);
            if (choice == 0) {
                a[v] = n;
            } else if (choice == 1) {
                a[v] = hub;
            } else if (choice == 2) {
                a[v] = v;
            } else {
                a[v] = rnd.any(nodes);
            }
        }
        a[hub] = rnd.next(0, 1) ? n : hub;
    } else {
        int split = rnd.next(1, n - 1);
        for (int i = 0; i < split; ++i) {
            a[nodes[i]] = (i + 1 == split) ? n : nodes[i + 1];
        }
        for (int i = split; i < n - 1; ++i) {
            a[nodes[i]] = nodes[rnd.next(split, n - 2)];
        }
    }

    a[n] = rnd.next(0, 3) == 0 ? rnd.next(1, n) : n;

    vector<int> out(a.begin() + 1, a.end());
    println(n);
    println(out);

    return 0;
}
