#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 0;
    vector<int> parent(1, -1);

    auto add_node = [&](int p) {
        parent.push_back(p);
        return static_cast<int>(parent.size()) - 1;
    };

    if (mode == 0) {
        n = rnd.next(1, 30);
        parent.resize(n + 1);
        parent[0] = -1;
        for (int i = 1; i <= n; ++i) {
            parent[i] = i - 1;
        }
    } else if (mode == 1) {
        n = rnd.next(2, 35);
        parent.resize(n + 1);
        parent[0] = -1;
        for (int i = 1; i <= n; ++i) {
            parent[i] = 0;
        }
    } else if (mode == 2) {
        int target = rnd.next(6, 45);
        for (int i = 1; i <= target; ++i) {
            int p = (i == 1 ? 0 : rnd.next(max(0, i / 3), i - 1));
            add_node(p);
        }
        n = target;
    } else if (mode == 3) {
        int spine = rnd.next(2, 12);
        int last = 0;
        for (int i = 0; i < spine; ++i) {
            last = add_node(last);
            int sideLeaves = rnd.next(0, 3);
            for (int j = 0; j < sideLeaves; ++j) {
                add_node(last);
            }
        }
        int extra = rnd.next(1, 8);
        for (int i = 0; i < extra; ++i) {
            add_node(rnd.next(0, last));
        }
        n = static_cast<int>(parent.size()) - 1;
    } else {
        int layers = rnd.next(2, 5);
        vector<int> frontier = {0};
        for (int layer = 0; layer < layers; ++layer) {
            vector<int> next;
            shuffle(frontier.begin(), frontier.end());
            for (int p : frontier) {
                int childCount = rnd.next(layer + 1 == layers ? 0 : 1, 4);
                for (int i = 0; i < childCount; ++i) {
                    if (static_cast<int>(parent.size()) > 50) {
                        break;
                    }
                    next.push_back(add_node(p));
                }
            }
            if (next.empty()) {
                next.push_back(add_node(rnd.any(frontier)));
            }
            frontier = next;
        }
        n = static_cast<int>(parent.size()) - 1;
    }

    vector<int> childCount(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        ++childCount[parent[i]];
    }

    vector<int> leaves;
    for (int i = 1; i <= n; ++i) {
        if (childCount[i] == 0) {
            leaves.push_back(i);
        }
    }
    shuffle(leaves.begin(), leaves.end());

    println(n);
    vector<int> parents(parent.begin() + 1, parent.end());
    println(parents);
    for (int leaf : leaves) {
        println(leaf);
    }

    return 0;
}
