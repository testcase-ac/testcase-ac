#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

static vector<int> relabelMap(const vector<int>& next) {
    int n = (int)next.size() - 1;
    vector<int> labels(n + 1);
    iota(labels.begin(), labels.end(), 0);
    shuffle(labels.begin() + 1, labels.end());

    vector<int> mapped(n + 1);
    for (int i = 1; i <= n; ++i) {
        mapped[labels[i]] = labels[next[i]];
    }
    return mapped;
}

static vector<int> makePermutation(int n) {
    vector<int> p(n + 1);
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);
    shuffle(order.begin(), order.end());

    int pos = 0;
    while (pos < n) {
        int remaining = n - pos;
        int len = (remaining <= 2) ? remaining : rnd.next(1, min(remaining, 8));
        for (int i = 0; i < len; ++i) {
            p[order[pos + i]] = order[pos + (i + 1) % len];
        }
        pos += len;
    }
    return p;
}

static vector<int> makeCycleWithTrees(int n) {
    vector<int> a(n + 1);
    int cycleLen = rnd.next(1, n);
    for (int i = 1; i < cycleLen; ++i) {
        a[i] = i + 1;
    }
    a[cycleLen] = 1;

    for (int i = cycleLen + 1; i <= n; ++i) {
        a[i] = rnd.next(1, i - 1);
    }
    return relabelMap(a);
}

static vector<int> makeManyToOne(int n) {
    vector<int> a(n + 1);
    int sink = rnd.next(1, n);
    for (int i = 1; i <= n; ++i) {
        a[i] = sink;
    }
    if (rnd.next(2) == 0) {
        a[sink] = rnd.next(1, n);
    }
    return a;
}

static vector<int> makeMixedComponents(int n) {
    vector<int> a(n + 1, 0);
    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end());

    int pos = 0;
    while (pos < n) {
        int remaining = n - pos;
        int size = rnd.next(1, min(remaining, 10));
        int cycleLen = rnd.next(1, size);

        for (int i = 0; i < cycleLen; ++i) {
            a[nodes[pos + i]] = nodes[pos + (i + 1) % cycleLen];
        }
        for (int i = cycleLen; i < size; ++i) {
            a[nodes[pos + i]] = nodes[pos + rnd.next(i)];
        }
        pos += size;
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(2, 60);
    if (rnd.next(10) == 0) {
        n = rnd.next(61, 200);
    }

    vector<int> a;
    if (mode == 0) {
        a = makePermutation(n);
    } else if (mode == 1) {
        a = makeCycleWithTrees(n);
    } else if (mode == 2) {
        a = makeManyToOne(n);
    } else if (mode == 3) {
        a.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            a[i] = (i == n ? n : i + 1);
        }
        a = relabelMap(a);
    } else {
        a = makeMixedComponents(n);
    }

    vector<int> out(a.begin() + 1, a.end());
    println(n);
    println(out);

    return 0;
}
