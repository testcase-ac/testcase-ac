#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    int m = 1;

    if (mode == 0) {
        n = rnd.next(1, 6);
        m = rnd.next(1, 6);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 10);
    } else if (mode == 2) {
        n = rnd.next(2, 9);
        m = rnd.next(2, 9);
    } else if (mode == 3) {
        n = rnd.next(3, 12);
        m = rnd.next(3, 12);
    } else if (mode == 4) {
        n = rnd.next(1, 14);
        m = rnd.next(1, 14);
    } else {
        n = rnd.next(8, 18);
        m = rnd.next(8, 18);
    }

    vector<vector<int>> adj(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                adj[i].push_back(rnd.next(1, m));
            }
        }
    } else if (mode == 1) {
        int left = rnd.next(1, n);
        int right = rnd.next(1, m);
        for (int i = 0; i < left; ++i) {
            for (int b = 1; b <= right; ++b) {
                adj[i].push_back(b);
            }
        }
    } else if (mode == 2) {
        int len = min(n, m);
        for (int i = 0; i < len; ++i) {
            adj[i].push_back(i + 1);
            if (i + 1 < len) {
                adj[i].push_back(i + 2);
            }
        }
    } else if (mode == 3) {
        int hubs = rnd.next(1, min(m, 4));
        for (int i = 0; i < n; ++i) {
            for (int b = 1; b <= hubs; ++b) {
                adj[i].push_back(b);
            }
            if (hubs < m && rnd.next(0, 1) == 1) {
                adj[i].push_back(rnd.next(hubs + 1, m));
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            vector<int> choices;
            for (int b = 1; b <= m; ++b) {
                choices.push_back(b);
            }
            shuffle(choices.begin(), choices.end());
            int degree = rnd.next(0, min(m, 5));
            choices.resize(degree);
            adj[i] = choices;
        }
    } else {
        int band = rnd.next(1, min(m, 5));
        for (int i = 0; i < n; ++i) {
            for (int offset = 0; offset < band; ++offset) {
                int b = (i + offset) % m + 1;
                adj[i].push_back(b);
            }
            if (rnd.next(0, 2) == 0) {
                adj[i].push_back(rnd.next(1, m));
            }
            sort(adj[i].begin(), adj[i].end());
            adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
        }
    }

    for (auto& row : adj) {
        shuffle(row.begin(), row.end());
    }

    println(n, m);
    for (const auto& row : adj) {
        cout << row.size();
        for (int b : row) {
            cout << ' ' << b;
        }
        cout << '\n';
    }

    return 0;
}
