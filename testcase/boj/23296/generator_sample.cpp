#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int otherFloor(int n, int self) {
    int x = rnd.next(1, n - 1);
    if (x >= self) {
        ++x;
    }
    return x;
}

void makeCycle(vector<int>& to, const vector<int>& nodes) {
    int m = (int)nodes.size();
    for (int i = 0; i < m; ++i) {
        to[nodes[i]] = nodes[(i + 1) % m];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 5 ? rnd.next(30, 120) : rnd.next(2, 16);
    vector<int> to(n + 1, 0);

    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            to[i] = otherFloor(n, i);
        }
    } else if (mode == 1) {
        int sink = rnd.next(1, n);
        to[sink] = otherFloor(n, sink);
        for (int i = 1; i <= n; ++i) {
            if (i != sink) {
                to[i] = sink;
            }
        }
    } else if (mode == 2) {
        vector<int> nodes(n);
        iota(nodes.begin(), nodes.end(), 1);
        shuffle(nodes.begin(), nodes.end());
        makeCycle(to, nodes);
    } else if (mode == 3) {
        for (int i = 1; i < n; ++i) {
            to[i] = i + 1;
        }
        to[n] = rnd.next(1, n - 1);
        if (rnd.next(0, 1)) {
            reverse(to.begin() + 1, to.end());
            for (int i = 1; i <= n; ++i) {
                if (to[i] == i) {
                    to[i] = otherFloor(n, i);
                }
            }
        }
    } else if (mode == 4) {
        vector<int> nodes(n);
        iota(nodes.begin(), nodes.end(), 1);
        shuffle(nodes.begin(), nodes.end());
        int pos = 0;
        while (pos < n) {
            int remaining = n - pos;
            if (remaining == 1) {
                int lone = nodes[pos];
                int target = nodes[rnd.next(0, pos - 1)];
                to[lone] = to[target];
                to[target] = lone;
                break;
            }
            int len = remaining == 2 ? 2 : rnd.next(2, min(remaining, 6));
            vector<int> cycle(nodes.begin() + pos, nodes.begin() + pos + len);
            makeCycle(to, cycle);
            pos += len;
        }
    } else {
        vector<int> anchors;
        int anchorCount = rnd.next(2, min(n, 8));
        for (int i = 1; i <= anchorCount; ++i) {
            anchors.push_back(i);
        }
        shuffle(anchors.begin(), anchors.end());
        makeCycle(to, anchors);
        for (int i = anchorCount + 1; i <= n; ++i) {
            int parent = rnd.next(1, i - 1);
            to[i] = parent == i ? otherFloor(n, i) : parent;
        }
        vector<int> labels(n);
        iota(labels.begin(), labels.end(), 1);
        shuffle(labels.begin(), labels.end());
        vector<int> relabeled(n + 1);
        for (int i = 1; i <= n; ++i) {
            relabeled[labels[i - 1]] = labels[to[i] - 1];
        }
        to.swap(relabeled);
    }

    for (int i = 1; i <= n; ++i) {
        if (to[i] == i) {
            to[i] = otherFloor(n, i);
        }
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            cout << ' ';
        }
        cout << to[i];
    }
    cout << '\n';

    return 0;
}
