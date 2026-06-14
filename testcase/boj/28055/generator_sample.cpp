#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static vector<int> makeParents(int n, int mode) {
    vector<int> parent(n + 1, 0);
    if (n == 1) {
        return parent;
    }

    if (mode == 0) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = i - 1;
        }
    } else if (mode == 1) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = 1;
        }
    } else if (mode == 2) {
        for (int i = 2; i <= n; ++i) {
            parent[i] = i / 2;
        }
    } else if (mode == 3) {
        int stem = rnd.next(1, n);
        for (int i = 2; i <= stem; ++i) {
            parent[i] = i - 1;
        }
        for (int i = stem + 1; i <= n; ++i) {
            parent[i] = rnd.next(1, stem);
        }
    } else if (mode == 4) {
        for (int i = 2; i <= n; ++i) {
            int depthBias = rnd.next(0, 2);
            if (depthBias == 0) {
                parent[i] = rnd.next(1, i - 1);
            } else if (depthBias == 1) {
                parent[i] = max(1, i - rnd.next(1, min(i - 1, 4)));
            } else {
                parent[i] = 1;
            }
        }
    } else {
        int spine = rnd.next(1, n);
        for (int i = 2; i <= spine; ++i) {
            parent[i] = i - 1;
        }
        for (int i = spine + 1; i <= n; ++i) {
            parent[i] = rnd.next(max(1, spine / 2), spine);
        }
    }

    return parent;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(0, 9);
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 5) {
        n = rnd.next(2, 12);
    } else if (sizeMode <= 8) {
        n = rnd.next(13, 40);
    } else {
        n = rnd.next(41, 80);
    }

    vector<int> parent = makeParents(n, rnd.next(0, 5));

    vector<int> label(n + 1);
    label[1] = 1;
    vector<int> nonRoot;
    for (int i = 2; i <= n; ++i) {
        nonRoot.push_back(i);
    }
    shuffle(nonRoot.begin(), nonRoot.end());
    for (int i = 2; i <= n; ++i) {
        label[i] = nonRoot[i - 2];
    }

    vector<int> outputParent(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        outputParent[label[i]] = label[parent[i]];
    }

    println(n);
    for (int i = 2; i <= n; ++i) {
        println(outputParent[i]);
    }

    return 0;
}
