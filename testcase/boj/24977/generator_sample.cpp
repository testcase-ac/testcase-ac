#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 24);
    vector<int> to;

    auto makeCycle = [&](const vector<int>& nodes) {
        for (int i = 0; i < (int)nodes.size(); ++i) {
            to[nodes[i]] = nodes[(i + 1) % nodes.size()];
        }
    };

    if (mode == 0) {
        n = rnd.next(2, 18);
        to.assign(n + 1, 0);
        vector<int> nodes(n);
        iota(nodes.begin(), nodes.end(), 1);
        makeCycle(nodes);
    } else if (mode == 1) {
        n = rnd.next(4, 24);
        to.assign(n + 1, 0);
        vector<int> remaining(n);
        iota(remaining.begin(), remaining.end(), 1);
        int pos = 0;
        while (n - pos >= 2) {
            int left = n - pos;
            int len = (left <= 3) ? left : rnd.next(2, min(7, left));
            vector<int> cycle;
            for (int i = 0; i < len; ++i) cycle.push_back(remaining[pos++]);
            makeCycle(cycle);
        }
        if (pos < n) {
            to[remaining[pos]] = rnd.next(1, n - 1);
        }
    } else if (mode == 2) {
        n = rnd.next(5, 25);
        to.assign(n + 1, 0);
        to[1] = 2;
        to[2] = 1;
        for (int i = 3; i <= n; ++i) {
            to[i] = rnd.next(1, i - 1);
        }
    } else if (mode == 3) {
        n = rnd.next(8, 30);
        to.assign(n + 1, 0);
        int cycleLen = rnd.next(3, min(8, n));
        vector<int> cycle;
        for (int i = 1; i <= cycleLen; ++i) cycle.push_back(i);
        makeCycle(cycle);
        for (int i = cycleLen + 1; i <= n; ++i) {
            to[i] = rnd.next(1, i - 1);
        }
    } else {
        n = rnd.next(2, 30);
        to.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            int dest = rnd.next(1, n - 1);
            if (dest >= i) ++dest;
            to[i] = dest;
        }
    }

    vector<long long> values(n + 1);
    int valueMode = rnd.next(0, 4);
    for (int i = 1; i <= n; ++i) {
        if (valueMode == 0) {
            values[i] = rnd.next(0, 25);
        } else if (valueMode == 1) {
            values[i] = (rnd.next(0, 4) == 0) ? 0 : rnd.next(1, 1000);
        } else if (valueMode == 2) {
            values[i] = 1000000000LL - rnd.next(0, 1000);
        } else if (valueMode == 3) {
            values[i] = (i % 2 == 0) ? 0 : 1000000000LL;
        } else {
            values[i] = rnd.next(0, 1000000000);
        }
    }

    vector<int> shuffledLabels(n);
    iota(shuffledLabels.begin(), shuffledLabels.end(), 1);
    shuffle(shuffledLabels.begin(), shuffledLabels.end());

    vector<int> label(n + 1);
    for (int i = 1; i <= n; ++i) {
        label[i] = shuffledLabels[i - 1];
    }

    vector<int> outTo(n + 1);
    vector<long long> outValue(n + 1);
    for (int i = 1; i <= n; ++i) {
        outTo[label[i]] = label[to[i]];
        outValue[label[i]] = values[i];
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        println(outTo[i], outValue[i]);
    }

    return 0;
}
