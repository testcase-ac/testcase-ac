#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using int64 = long long;

static int64 parentOf(int64 node, int k) {
    if (node == 1) return 1;
    return (node - 2) / k + 1;
}

static int64 firstChildOf(int64 node, int k) {
    return (node - 1) * (int64)k + 2;
}

static int64 randomNode(int64 n) {
    int mode = rnd.next(0, 4);
    if (mode == 0) return rnd.next(1LL, min<int64>(n, 20));
    if (mode == 1) return rnd.next(max<int64>(1, n - 20), n);
    return rnd.next(1LL, n);
}

static int64 descendRandomly(int64 node, int64 n, int k) {
    int steps = rnd.next(1, 7);
    for (int i = 0; i < steps; ++i) {
        int64 firstChild = firstChildOf(node, k);
        if (firstChild > n) break;
        int64 lastChild = min<int64>(n, firstChild + k - 1);
        node = rnd.next(firstChild, lastChild);
    }
    return node;
}

static pair<int64, int64> makeQuery(int64 n, int k) {
    int mode = rnd.next(0, 7);

    if (k == 1) {
        int64 x = randomNode(n);
        int64 y = randomNode(n);
        while (x == y) y = randomNode(n);
        return {x, y};
    }

    if (mode == 0 && n >= 2) {
        int64 child = rnd.next(2LL, n);
        return {parentOf(child, k), child};
    }

    if (mode == 1) {
        int64 ancestor = randomNode(n);
        int64 child = descendRandomly(ancestor, n, k);
        if (child != ancestor) return {ancestor, child};
    }

    if (mode == 2) {
        int64 parent = randomNode(n);
        int64 firstChild = firstChildOf(parent, k);
        if (firstChild <= n) {
            int64 lastChild = min<int64>(n, firstChild + k - 1);
            if (firstChild < lastChild) {
                int64 x = rnd.next(firstChild, lastChild);
                int64 y = rnd.next(firstChild, lastChild);
                while (x == y) y = rnd.next(firstChild, lastChild);
                return {x, y};
            }
        }
    }

    if (mode == 3) {
        int64 x = rnd.next(max<int64>(1, n - min<int64>(n - 1, 50)), n);
        int64 y = randomNode(n);
        while (x == y) y = randomNode(n);
        return {x, y};
    }

    int64 x = randomNode(n);
    int64 y = randomNode(n);
    while (x == y) y = randomNode(n);
    return {x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> kChoices = {1, 2, 3, 4, 10, 1000};
    int k = rnd.any(kChoices);
    if (rnd.next(0, 2) == 0) k = rnd.next(1, 1000);

    int64 n;
    int sizeMode = rnd.next(0, 5);
    if (sizeMode == 0) {
        n = rnd.next(2LL, 20LL);
    } else if (sizeMode == 1) {
        n = rnd.next(21LL, 1000LL);
    } else if (sizeMode == 2) {
        n = rnd.next(1000000000000LL, 1000000000000000LL);
    } else {
        int depth = rnd.next(2, 12);
        n = 1;
        int64 level = 1;
        for (int i = 0; i < depth && level <= 1000000000000000LL / max(1, k); ++i) {
            level *= k;
            if (n > 1000000000000000LL - level) break;
            n += level;
        }
        n = max<int64>(2, n - rnd.next(0LL, min<int64>(n - 2, 20)));
    }

    int q = rnd.next(1, 30);
    vector<pair<int64, int64>> queries;
    for (int i = 0; i < q; ++i) queries.push_back(makeQuery(n, k));

    println(n, k, q);
    for (auto [x, y] : queries) println(x, y);

    return 0;
}
