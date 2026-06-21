#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> makePath(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        edges.push_back({i - 1, i});
    }
    return edges;
}

vector<pair<int, int>> makeStar(int n) {
    vector<pair<int, int>> edges;
    int center = rnd.next(0, n - 1);
    for (int i = 0; i < n; ++i) {
        if (i != center) {
            edges.push_back({center, i});
        }
    }
    return edges;
}

vector<pair<int, int>> makeBinaryLikeTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        edges.push_back({rnd.next(max(0, (i - 2) / 2), (i - 1) / 2), i});
    }
    return edges;
}

vector<pair<int, int>> makeBroom(int n) {
    vector<pair<int, int>> edges;
    int handle = rnd.next(1, n - 1);
    for (int i = 1; i <= handle; ++i) {
        edges.push_back({i - 1, i});
    }
    int hub = rnd.next(0, handle);
    for (int i = handle + 1; i < n; ++i) {
        edges.push_back({hub, i});
    }
    return edges;
}

vector<pair<int, int>> makeRandomTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        int parent = rnd.next(0, i - 1);
        edges.push_back({parent, i});
    }
    return edges;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = rnd.next(2, 5);
    } else if (sizeMode == 1) {
        n = rnd.next(6, 12);
    } else if (sizeMode == 2) {
        n = rnd.next(13, 24);
    } else if (sizeMode == 3) {
        n = rnd.next(25, 35);
    } else {
        n = rnd.next(36, 51);
    }

    vector<pair<int, int>> edges;
    int treeMode = rnd.next(0, 4);
    if (treeMode == 0) {
        edges = makePath(n);
    } else if (treeMode == 1) {
        edges = makeStar(n);
    } else if (treeMode == 2) {
        edges = makeBinaryLikeTree(n);
    } else if (treeMode == 3) {
        edges = makeBroom(n);
    } else {
        edges = makeRandomTree(n);
    }

    vector<int> perm(n);
    for (int i = 0; i < n; ++i) {
        perm[i] = i;
    }
    shuffle(perm.begin(), perm.end());
    shuffle(edges.begin(), edges.end());

    int mMode = rnd.next(0, 3);
    int m;
    if (mMode == 0) {
        m = rnd.next(1, min(5, 50));
    } else if (mMode == 1) {
        m = rnd.next(1, min(n, 50));
    } else if (mMode == 2) {
        m = rnd.next(max(1, min(10, n)), 30);
    } else {
        m = rnd.next(31, 50);
    }

    vector<int> families;
    int familyMode = rnd.next(0, 3);
    if (familyMode == 0) {
        int city = rnd.next(0, n - 1);
        families.assign(m, city);
    } else if (familyMode == 1) {
        int a = rnd.next(0, n - 1);
        int b = rnd.next(0, n - 2);
        if (b >= a) {
            ++b;
        }
        for (int i = 0; i < m; ++i) {
            families.push_back(rnd.next(0, 1) == 0 ? a : b);
        }
    } else if (familyMode == 2) {
        for (int i = 0; i < m; ++i) {
            families.push_back(i % n);
        }
        shuffle(families.begin(), families.end());
    } else {
        for (int i = 0; i < m; ++i) {
            families.push_back(rnd.next(0, n - 1));
        }
    }

    println(n, m);
    for (auto [a, b] : edges) {
        if (rnd.next(0, 1) == 0) {
            swap(a, b);
        }
        println(perm[a], perm[b]);
    }
    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << perm[families[i]];
    }
    cout << '\n';

    return 0;
}
