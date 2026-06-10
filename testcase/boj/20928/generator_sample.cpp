#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    int m = rnd.next(1, 80);

    vector<int> p;
    if (mode == 0) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 20);
        p.push_back(rnd.next(1, m));
        while ((int)p.size() < n) {
            int next = p.back() + rnd.next(1, 5);
            if (next > 100) break;
            p.push_back(next);
        }
    } else if (mode == 1) {
        n = rnd.next(4, 16);
        m = rnd.next(n, n + 20);
        int cur = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            p.push_back(cur);
            cur += rnd.next(1, 3);
        }
        m = max(m, p[0]);
    } else if (mode == 2) {
        n = rnd.next(2, 14);
        m = rnd.next(10, 70);
        int cur = rnd.next(1, min(5, m));
        for (int i = 0; i < n; ++i) {
            p.push_back(cur);
            cur += rnd.next(4, 12);
        }
    } else if (mode == 3) {
        n = rnd.next(6, 18);
        m = rnd.next(20, 80);
        int cur = rnd.next(1, min(4, m));
        for (int i = 0; i < n; ++i) {
            p.push_back(cur);
            cur += rnd.next(1, 8);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        m = rnd.next(5, 40);
        int cur = rnd.next(1, m);
        for (int i = 0; i < n; ++i) {
            p.push_back(cur);
            cur += rnd.next(1, 10);
        }
    } else {
        n = rnd.next(2, 15);
        m = rnd.next(2, 60);
        p.push_back(rnd.next(1, m));
        while ((int)p.size() < n) {
            p.push_back(p.back() + rnd.next(1, 6));
        }
        if (rnd.next(0, 1) == 1) {
            m = p[rnd.next(0, (int)p.size() - 1)];
        }
    }

    n = (int)p.size();
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            x[i] = rnd.next(1, 10000);
        } else if (mode == 1) {
            x[i] = rnd.next(1, 4);
        } else if (mode == 2) {
            x[i] = rnd.next(1, 3);
        } else if (mode == 3) {
            x[i] = rnd.next(1, 12);
        } else if (mode == 4) {
            x[i] = rnd.next(1, 10);
            if (i == 0 && rnd.next(0, 2) == 0) {
                x[i] = max(1, m - p[i]);
            }
        } else {
            int target = rnd.next(p[i], max(p[i], m));
            x[i] = rnd.next(1, max(1, target - p[i] + 1));
        }
    }

    println(n, m);
    println(p);
    println(x);
    return 0;
}
