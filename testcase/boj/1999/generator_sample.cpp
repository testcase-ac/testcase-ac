#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(6);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode <= 2) {
        n = rnd.next(2, 6);
    } else {
        n = rnd.next(7, 15);
    }

    int bMode = rnd.next(5);
    int b;
    if (bMode == 0) {
        b = 1;
    } else if (bMode == 1) {
        b = n;
    } else if (bMode == 2) {
        b = rnd.next(1, min(n, 3));
    } else {
        b = rnd.next(1, n);
    }

    int qLimit = n - b + 1;
    int k = rnd.next(1, min(40, qLimit * qLimit + 8));

    vector<vector<int>> a(n, vector<int>(n));
    int valueMode = rnd.next(6);
    int lo = rnd.next(0, 250);
    int hi = rnd.next(lo, 250);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (valueMode == 0) {
                a[i][j] = lo;
            } else if (valueMode == 1) {
                a[i][j] = ((i + j) % 2 == 0 ? 0 : 250);
            } else if (valueMode == 2) {
                a[i][j] = (i * 17 + j * 29 + rnd.next(0, 7)) % 251;
            } else if (valueMode == 3) {
                a[i][j] = rnd.next(lo, hi);
            } else if (valueMode == 4) {
                a[i][j] = rnd.next(0, 4) == 0 ? 250 : rnd.next(0, 20);
            } else {
                a[i][j] = rnd.next(0, 4) == 0 ? 0 : rnd.next(230, 250);
            }
        }
    }

    vector<pair<int, int>> queries;
    queries.emplace_back(1, 1);
    queries.emplace_back(qLimit, qLimit);
    if (qLimit > 1) {
        queries.emplace_back(1, qLimit);
        queries.emplace_back(qLimit, 1);
    }

    while ((int)queries.size() < k) {
        int queryMode = rnd.next(4);
        if (queryMode == 0) {
            queries.emplace_back(1, rnd.next(1, qLimit));
        } else if (queryMode == 1) {
            queries.emplace_back(rnd.next(1, qLimit), 1);
        } else if (queryMode == 2) {
            queries.emplace_back(qLimit, rnd.next(1, qLimit));
        } else {
            queries.emplace_back(rnd.next(1, qLimit), rnd.next(1, qLimit));
        }
    }
    shuffle(queries.begin(), queries.end());
    queries.resize(k);

    println(n, b, k);
    for (int i = 0; i < n; ++i) {
        println(a[i]);
    }
    for (auto [r, c] : queries) {
        println(r, c);
    }

    return 0;
}
