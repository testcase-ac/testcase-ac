#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int differentFrom(int n, int first, int second = -1) {
    int value = rnd.next(1, n);
    while (value == first || value == second) {
        value = rnd.next(1, n);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(3, 15);
    int maxM = min(45, n * (n - 1) * (n - 2));
    int m = rnd.next(1, maxM);

    vector<int> t(n + 1, 3);
    if (mode == 0) {
        for (int i = 1; i <= n; ++i) {
            t[i] = rnd.next(1, 3);
        }
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            t[i] = rnd.next(0, 9) < 7 ? 3 : rnd.next(1, 2);
        }
    } else if (mode == 2) {
        int spy = rnd.next(1, n);
        int knownClean = differentFrom(n, spy);
        t[spy] = 1;
        t[knownClean] = 2;
        for (int i = 1; i <= n; ++i) {
            if (t[i] == 3 && rnd.next(0, 3) == 0) {
                t[i] = rnd.next(1, 2);
            }
        }
    } else {
        int first = rnd.next(1, n);
        t[first] = rnd.next(1, 2);
        for (int i = 1; i <= n; ++i) {
            if (i != first && rnd.next(0, 4) == 0) {
                t[i] = rnd.next(1, 3);
            }
        }
    }

    vector<vector<int>> rows;
    rows.reserve(m);

    if (mode == 3) {
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            p[i] = i + 1;
        }
        shuffle(p.begin(), p.end());
        for (int i = 0; i + 2 < n && (int)rows.size() < m; ++i) {
            rows.push_back({p[i], p[i + 1], p[i + 2]});
        }
    }

    while ((int)rows.size() < m) {
        int a = rnd.next(1, n);
        int b = differentFrom(n, a);
        int c = differentFrom(n, a, b);

        if (mode == 2 && rnd.next(0, 2) == 0) {
            vector<int> forced;
            for (int i = 1; i <= n; ++i) {
                if (t[i] == 1 || t[i] == 2) {
                    forced.push_back(i);
                }
            }
            if ((int)forced.size() >= 2) {
                b = rnd.any(forced);
                c = rnd.any(forced);
                while (c == b) {
                    c = rnd.any(forced);
                }
                a = differentFrom(n, b, c);
            }
        }

        rows.push_back({a, b, c});
    }

    println(n, m);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            printf(" ");
        }
        printf("%d", t[i]);
    }
    printf("\n");
    for (const vector<int>& row : rows) {
        println(row);
    }

    return 0;
}
