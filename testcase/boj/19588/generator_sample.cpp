#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else if (mode == 2) {
        n = rnd.next(7, 14);
    } else if (mode == 3) {
        n = rnd.next(12, 24);
    } else if (mode == 4) {
        n = rnd.next(20, 40);
    } else {
        n = rnd.next(35, 70);
    }

    int m;
    if (mode == 0) {
        m = 1;
    } else if (rnd.next(0, 4) == 0) {
        m = 1;
    } else if (rnd.next(0, 4) == 0) {
        m = n;
    } else {
        m = rnd.next(2, n);
    }

    vector<int> xs;
    set<int> used;
    int skillMode = rnd.next(0, 3);
    int base = rnd.next(1, 1000000000 - 3 * n);
    for (int i = 0; i < n; ++i) {
        int x;
        if (skillMode == 0) {
            x = i + 1;
        } else if (skillMode == 1) {
            x = 1000000000 - i;
        } else if (skillMode == 2) {
            x = base + 3 * i;
        } else {
            do {
                x = rnd.next(1, 1000000000);
            } while (used.count(x));
        }
        xs.push_back(x);
        used.insert(x);
    }

    if (rnd.next(0, 1)) {
        shuffle(xs.begin(), xs.end());
    }

    vector<int> ys(n);
    int nameMode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        if (nameMode == 0) {
            ys[i] = i + 1;
        } else if (nameMode == 1) {
            ys[i] = (1 << rnd.next(0, 20));
        } else if (nameMode == 2) {
            ys[i] = rnd.next(1, 255);
        } else if (nameMode == 3) {
            ys[i] = 1000000000 - i;
        } else {
            ys[i] = rnd.next(1, 1000000000);
        }
    }

    int q = rnd.next(1, min(40, max(1, 2 * n)));
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; ++i) {
        int maxTeams = n / m;
        int a;
        if (rnd.next(0, 3) == 0) {
            a = maxTeams;
        } else {
            a = rnd.next(1, maxTeams);
        }
        int maxB = n - m * a;
        int b;
        if (maxB == 0) {
            b = 0;
        } else if (rnd.next(0, 3) == 0) {
            b = maxB;
        } else {
            b = rnd.next(0, maxB);
        }
        queries.push_back({a, b});
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(xs[i], ys[i]);
    }
    println(q);
    for (auto query : queries) {
        println(query.first, query.second);
    }

    return 0;
}
