#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int chooseN(int mode) {
    if (mode == 0) return 1;
    if (mode == 5 && rnd.next(4) == 0) return rnd.next(20, 50);
    return rnd.next(2, 12);
}

void addRandomEdges(vector<string>& g, const vector<int>& order, int percent,
                    bool forwardOnly) {
    int n = (int)g.size();
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) pos[order[i]] = i;

    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (u == v) continue;
            if (forwardOnly && pos[u] >= pos[v]) continue;
            if (rnd.next(100) < percent) g[u][v] = '1';
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = chooseN(mode);
    vector<string> g(n, string(n, '0'));

    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    shuffle(order.begin(), order.end());

    if (mode == 0) {
        g[0][0] = rnd.next(2) ? '1' : '0';
    } else if (mode == 1) {
        addRandomEdges(g, order, rnd.next(15, 75), true);
    } else if (mode == 2) {
        addRandomEdges(g, order, rnd.next(5, 35), true);
        int len = rnd.next(2, n);
        for (int i = 0; i < len; ++i) {
            int u = order[i];
            int v = order[(i + 1) % len];
            g[u][v] = '1';
        }
    } else if (mode == 3) {
        addRandomEdges(g, order, rnd.next(0, 45), true);
        int loops = rnd.next(1, n);
        shuffle(order.begin(), order.end());
        for (int i = 0; i < loops; ++i) g[order[i]][order[i]] = '1';
    } else if (mode == 4) {
        int percent = rnd.next(0, 90);
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (u != v && rnd.next(100) < percent) g[u][v] = '1';
            }
        }
    } else {
        addRandomEdges(g, order, rnd.next(40, 95), true);
    }

    println(n);
    for (const string& row : g) println(row);

    return 0;
}
