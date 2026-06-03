#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 14);
    int mode = rnd.next(5);

    vector<int> labels;
    if (rnd.next(4) == 0) {
        int start = rnd.next(1, 10000 - n + 1);
        for (int i = 0; i < n; ++i) {
            labels.push_back(start + i);
        }
    } else {
        set<int> used;
        int compactLimit = rnd.next(n, min(40, 10000));
        while (static_cast<int>(labels.size()) < n) {
            int label = rnd.next(1, compactLimit);
            if (used.insert(label).second) {
                labels.push_back(label);
            }
        }
    }
    shuffle(labels.begin(), labels.end());

    vector<pair<int, int>> edges;
    if (mode == 0) {
        for (int i = 1; i < n; ++i) {
            edges.push_back({labels[i - 1], labels[i]});
        }
    } else if (mode == 1) {
        int center = labels[0];
        for (int i = 1; i < n; ++i) {
            edges.push_back({center, labels[i]});
        }
    } else if (mode == 2) {
        int spine = rnd.next(2, n);
        for (int i = 1; i < spine; ++i) {
            edges.push_back({labels[i - 1], labels[i]});
        }
        for (int i = spine; i < n; ++i) {
            edges.push_back({labels[rnd.next(0, spine - 1)], labels[i]});
        }
    } else if (mode == 3) {
        for (int i = 1; i < n; ++i) {
            edges.push_back({labels[(i - 1) / 2], labels[i]});
        }
    } else {
        for (int i = 1; i < n; ++i) {
            edges.push_back({labels[rnd.next(i)], labels[i]});
        }
    }

    shuffle(edges.begin(), edges.end());
    int weightMode = rnd.next(4);
    for (auto [u, v] : edges) {
        if (rnd.next(2) == 0) {
            swap(u, v);
        }

        int length;
        if (weightMode == 0) {
            length = 1;
        } else if (weightMode == 1) {
            length = rnd.next(1, 9);
        } else if (weightMode == 2) {
            length = rnd.next(10, 1000);
        } else {
            length = rnd.next(1, 100000);
        }
        println(u, v, length);
    }

    return 0;
}
