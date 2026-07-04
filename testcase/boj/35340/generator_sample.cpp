#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAX_A = 1000000000;

vector<int> increasingPrices(int n, int mode) {
    vector<int> a;

    if (mode == 0) {
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            a.push_back(cur);
            cur += rnd.next(1, 10);
        }
    } else if (mode == 1) {
        int cur = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            a.push_back(cur);
            cur += rnd.next(1, 1000000000 / max(1, n));
        }
    } else if (mode == 2) {
        int cur = MAX_A - n - rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            a.push_back(cur++);
        }
    } else {
        int cur = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            a.push_back(cur);
            cur += rnd.next(1, 4);
        }
    }

    return a;
}

vector<int> queries(int q, int n, int mode) {
    vector<int> x;
    vector<int> interesting = {1, 2, 3, 4, 7, 8, 15, 16, 31, 32, 63, 64,
                               100, 255, 256, 511, 512, 1023, 1024, MAX_A};
    shuffle(interesting.begin(), interesting.end());

    for (int value : interesting) {
        if ((int)x.size() == q) {
            break;
        }
        x.push_back(value);
    }

    while ((int)x.size() < q) {
        if (mode == 0) {
            x.push_back(rnd.next(1, 40));
        } else if (mode == 1) {
            int bit = rnd.next(0, min(n + 2, 29));
            int base = 1 << bit;
            x.push_back(max(1, min(MAX_A, base + rnd.next(-2, 2))));
        } else if (mode == 2) {
            x.push_back(rnd.next(900000000, MAX_A));
        } else {
            x.push_back(rnd.next(1, MAX_A));
        }
    }

    shuffle(x.begin(), x.end());
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int q;

    if (mode == 0) {
        n = rnd.next(1, 6);
        q = rnd.next(1, 10);
    } else if (mode == 1) {
        n = rnd.next(8, 18);
        q = rnd.next(8, 20);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        q = rnd.next(6, 15);
    } else if (mode == 3) {
        n = rnd.next(20, 45);
        q = rnd.next(10, 30);
    } else if (mode == 4) {
        n = 1;
        q = rnd.next(1, 12);
    } else {
        n = rnd.next(2, 30);
        q = rnd.next(1, 25);
    }

    vector<int> a = increasingPrices(n, mode % 4);
    vector<int> x = queries(q, n, mode % 4);

    println(n, q);
    println(a);
    for (int value : x) {
        println(value);
    }

    return 0;
}
