#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

vector<int> makeParents(int n, int mode) {
    vector<int> parents;
    parents.reserve(max(0, n - 1));

    for (int node = 2; node <= n; ++node) {
        int parent = 1;
        if (mode == 0) {
            parent = 1;
        } else if (mode == 1) {
            parent = node - 1;
        } else if (mode == 2) {
            parent = rnd.next(1, node - 1);
        } else if (mode == 3) {
            int spine = max(2, n / 2);
            parent = (node <= spine ? node - 1 : rnd.next(1, spine));
        } else {
            parent = (node <= 3 ? 1 : rnd.next(2, min(node - 1, 4)));
        }
        parents.push_back(parent);
    }

    return parents;
}

int chooseStep(int n, int flavor) {
    if (flavor == 0) {
        return 1;
    }
    if (flavor == 1) {
        return n;
    }
    if (flavor == 2) {
        return rnd.next(1, min(n, 3));
    }
    return rnd.next(1, n);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        int n;
        if (tc == 0) {
            n = 1;
        } else if (mode == 1) {
            n = rnd.next(2, 18);
        } else {
            n = rnd.next(2, 14);
        }

        int a = chooseStep(n, rnd.next(0, 3));
        int b = chooseStep(n, rnd.next(0, 3));
        if (rnd.next(0, 4) == 0) {
            b = a;
        }

        println(n, a, b);
        println(makeParents(n, mode));
    }

    return 0;
}
