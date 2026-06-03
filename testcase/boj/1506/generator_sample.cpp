#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
    } else if (mode == 2) {
        n = rnd.next(4, 14);
    } else {
        n = rnd.next(5, 15);
    }

    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    vector<int> cost(n);
    for (int i = 0; i < n; ++i) {
        if (rnd.next(0, 9) == 0) {
            cost[i] = 1000000;
        } else if (rnd.next(0, 2) == 0) {
            cost[i] = rnd.next(1, 20);
        } else {
            cost[i] = rnd.next(1, 1000000);
        }
    }

    vector<string> adj(n, string(n, '0'));
    auto addEdge = [&](int from, int to) {
        adj[order[from]][order[to]] = '1';
    };

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) addEdge(i, i);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) addEdge(i, (i + 1) % n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && rnd.next(0, 4) == 0) addEdge(i, j);
            }
        }
    } else if (mode == 2) {
        int blockCount = rnd.next(2, min(5, n));
        vector<vector<int>> blocks(blockCount);
        for (int i = 0; i < n; ++i) blocks[i % blockCount].push_back(i);

        for (auto& block : blocks) {
            if (block.empty()) continue;
            shuffle(block.begin(), block.end());
            for (int i = 0; i < (int)block.size(); ++i) {
                addEdge(block[i], block[(i + 1) % block.size()]);
            }
            for (int from : block) {
                for (int to : block) {
                    if (from != to && rnd.next(0, 3) == 0) addEdge(from, to);
                }
            }
        }

        for (int b = 0; b + 1 < blockCount; ++b) {
            int edges = rnd.next(1, 3);
            for (int k = 0; k < edges; ++k) {
                addEdge(rnd.any(blocks[b]), rnd.any(blocks[b + 1]));
            }
        }
        for (int b = 0; b < blockCount; ++b) {
            for (int c = b + 2; c < blockCount; ++c) {
                if (rnd.next(0, 2) == 0) addEdge(rnd.any(blocks[b]), rnd.any(blocks[c]));
            }
        }
    } else if (mode == 3) {
        for (int i = 0; i + 1 < n; ++i) addEdge(i, i + 1);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 2; j < n; ++j) {
                if (rnd.next(0, 3) == 0) addEdge(i, j);
            }
        }
    } else if (mode == 4) {
        double p = rnd.next(0.15, 0.55);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (rnd.next() < p) addEdge(i, j);
            }
        }
    } else {
        int hub = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i != hub) {
                addEdge(hub, i);
                if (rnd.next(0, 1) == 0) addEdge(i, hub);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i != j && rnd.next(0, 8) == 0) addEdge(i, j);
            }
        }
    }

    println(n);
    println(cost);
    for (const string& row : adj) println(row);

    return 0;
}
