#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Query {
    int l;
    int r;
    int k;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    vector<Query> queries;

    if (mode == 0) {
        n = rnd.next(1, 1000);
        m = 0;
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        m = rnd.next(1, min(1000, n * 3));
        for (int i = 0; i < m; ++i) {
            int p = rnd.next(1, n);
            queries.push_back({p, p, 1});
        }
    } else if (mode == 2) {
        n = rnd.next(2, 40);
        m = rnd.next(1, 80);
        for (int i = 0; i < m; ++i) {
            int k = rnd.next(1, n);
            queries.push_back({1, n, k});
        }
    } else if (mode == 3) {
        n = rnd.next(6, 60);
        m = rnd.next(10, 120);
        int center = rnd.next(1, n);
        for (int i = 0; i < m; ++i) {
            int radius = rnd.next(0, min(12, n - 1));
            int l = max(1, center - radius - rnd.next(0, 3));
            int r = min(n, center + radius + rnd.next(0, 3));
            if (l > r) swap(l, r);
            int len = r - l + 1;
            int k = rnd.next(1, len);
            queries.push_back({l, r, k});
        }
    } else if (mode == 4) {
        n = rnd.next(30, 120);
        m = rnd.next(30, 180);
        for (int i = 0; i < m; ++i) {
            int len = rnd.next(1, min(25, n));
            int l = rnd.next(1, n - len + 1);
            int r = l + len - 1;
            int k;
            int style = rnd.next(0, 2);
            if (style == 0) {
                k = 1;
            } else if (style == 1) {
                k = len;
            } else {
                k = rnd.next(1, len);
            }
            queries.push_back({l, r, k});
        }
    } else {
        n = rnd.next(200, 1000);
        m = rnd.next(200, 1000);
        for (int i = 0; i < m; ++i) {
            int l = rnd.next(1, n);
            int r = rnd.next(l, n);
            int len = r - l + 1;
            int k = rnd.next(1, len);
            queries.push_back({l, r, k});
        }
    }

    if (mode != 0) {
        shuffle(queries.begin(), queries.end());
        m = static_cast<int>(queries.size());
    }

    println(n, m);
    for (const Query& q : queries) {
        println(q.l, q.r, q.k);
    }

    return 0;
}
