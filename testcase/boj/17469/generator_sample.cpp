#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 15);
    int q = rnd.next(1, 25);

    if (mode == 0) {
        n = 1;
        q = rnd.next(1, 10);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
    } else if (mode == 2) {
        n = rnd.next(5, 15);
    }

    vector<int> parent(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (mode == 1) {
            parent[i] = i - 1;
        } else if (mode == 2) {
            parent[i] = 1;
        } else if (mode == 3) {
            parent[i] = max(1, i / 2);
        } else {
            parent[i] = rnd.next(1, i - 1);
        }
    }

    vector<int> color(n + 1);
    int palette = rnd.next(1, min(n, 6));
    int base = rnd.next(1, 100000 - palette + 1);
    for (int i = 1; i <= n; ++i) {
        if (mode == 0 || mode == 4) {
            color[i] = base;
        } else if (mode == 5) {
            color[i] = base + (i - 1) % palette;
        } else {
            color[i] = base + rnd.next(0, palette - 1);
        }
    }

    vector<pair<int, int>> queries;
    vector<int> deletions;
    for (int i = 2; i <= n; ++i) deletions.push_back(i);
    shuffle(deletions.begin(), deletions.end());

    int reportsLeft = q;
    int deletesLeft = n - 1;
    while (reportsLeft > 0 || deletesLeft > 0) {
        bool emitReport;
        if (reportsLeft == 0) {
            emitReport = false;
        } else if (deletesLeft == 0) {
            emitReport = true;
        } else if (mode == 1) {
            emitReport = rnd.next(0, 2) != 0;
        } else if (mode == 2) {
            emitReport = rnd.next(0, 2) == 0;
        } else {
            emitReport = rnd.next(0, 1) == 0;
        }

        if (emitReport) {
            int a = rnd.next(1, n);
            queries.push_back({2, a});
            --reportsLeft;
        } else {
            int a = deletions.back();
            deletions.pop_back();
            queries.push_back({1, a});
            --deletesLeft;
        }
    }

    println(n, q);
    for (int i = 2; i <= n; ++i) println(parent[i]);
    for (int i = 1; i <= n; ++i) println(color[i]);
    for (auto [x, a] : queries) println(x, a);

    return 0;
}
