#include "testlib.h"
#include <vector>

using namespace std;

int grundy(int x) {
    int g = 1;
    while (g * (g + 1) <= 2 * x) {
        ++g;
    }
    return g - 1;
}

void appendRandomRange(vector<int>& a, int count, int lo, int hi) {
    for (int i = 0; i < count; ++i) {
        a.push_back(rnd.next(lo, hi));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<vector<int>> byGrundy(11);
    for (int x = 1; x <= 60; ++x) {
        byGrundy[grundy(x)].push_back(x);
    }

    vector<int> a;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 40);
        appendRandomRange(a, n, 1, 60);
    } else if (mode == 1) {
        int n = rnd.next(2, 70);
        vector<int> pool = {1, 2, 3, 4, 5, 6, 7, 8, 55, 56, 57, 58, 59, 60};
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else if (mode == 2) {
        int distinct = rnd.next(1, 10);
        vector<int> pool;
        while ((int)pool.size() < distinct) {
            int x = rnd.next(1, 60);
            bool seen = false;
            for (int y : pool) {
                if (x == y) {
                    seen = true;
                }
            }
            if (!seen) {
                pool.push_back(x);
            }
        }
        int n = rnd.next(distinct, 90);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else if (mode == 3) {
        int pairs = rnd.next(1, 35);
        for (int i = 0; i < pairs; ++i) {
            int g = rnd.next(1, 10);
            int x = rnd.any(byGrundy[g]);
            int y = rnd.any(byGrundy[g]);
            a.push_back(x);
            a.push_back(y);
        }
        if (rnd.next(0, 1)) {
            int g = rnd.next(1, 10);
            a.push_back(rnd.any(byGrundy[g]));
        }
    } else if (mode == 4) {
        int n = rnd.next(45, 120);
        int lo = rnd.next(1, 50);
        int hi = rnd.next(lo, min(60, lo + rnd.next(0, 10)));
        appendRandomRange(a, n, lo, hi);
    } else {
        int n = rnd.next(1, 120);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 99);
            if (bucket < 45) {
                a.push_back(rnd.next(1, 10));
            } else if (bucket < 75) {
                a.push_back(rnd.next(11, 35));
            } else {
                a.push_back(rnd.next(36, 60));
            }
        }
    }

    shuffle(a.begin(), a.end());
    println((int)a.size());
    println(a);

    return 0;
}
