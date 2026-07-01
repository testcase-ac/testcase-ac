#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static vector<int> makeChain(int n) {
    vector<int> parent(n + 1);
    for (int i = 2; i <= n; ++i) {
        parent[i] = i - 1;
    }
    return parent;
}

static vector<int> makeStar(int n) {
    vector<int> parent(n + 1);
    for (int i = 2; i <= n; ++i) {
        parent[i] = 1;
    }
    return parent;
}

static vector<int> makeBalanced(int n, int arity) {
    vector<int> parent(n + 1);
    for (int i = 2; i <= n; ++i) {
        parent[i] = (i - 2) / arity + 1;
    }
    return parent;
}

static vector<int> makeBroom(int n) {
    vector<int> parent(n + 1);
    int handle = rnd.next(2, n);
    for (int i = 2; i <= handle; ++i) {
        parent[i] = i - 1;
    }
    for (int i = handle + 1; i <= n; ++i) {
        parent[i] = rnd.next(1, handle);
    }
    return parent;
}

static vector<int> makeRandomTree(int n) {
    vector<int> parent(n + 1);
    for (int i = 2; i <= n; ++i) {
        int bias = rnd.next(0, 2);
        if (bias == 0) {
            parent[i] = rnd.next(1, i - 1);
        } else if (bias == 1) {
            parent[i] = max(1, i - rnd.next(1, min(i - 1, 4)));
        } else {
            parent[i] = rnd.wnext(i - 1, -2) + 1;
        }
    }
    return parent;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 18);
    int mode = rnd.next(0, 5);
    vector<int> parent;

    if (n == 1) {
        parent.assign(n + 1, 0);
    } else if (mode == 0) {
        parent = makeChain(n);
    } else if (mode == 1) {
        parent = makeStar(n);
    } else if (mode == 2) {
        parent = makeBalanced(n, rnd.next(2, 4));
    } else if (mode == 3) {
        parent = makeBroom(n);
    } else {
        parent = makeRandomTree(n);
    }

    println(n);
    if (n > 1) {
        vector<int> parents;
        for (int i = 2; i <= n; ++i) {
            parents.push_back(parent[i]);
        }
        println(parents);
    }

    return 0;
}
