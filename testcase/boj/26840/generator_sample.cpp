#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int b;
    if (mode == 0) {
        b = 2;
    } else if (mode == 1) {
        b = rnd.next(3, 5);
    } else if (mode == 2) {
        b = rnd.next(6, 12);
    } else {
        b = rnd.next(13, 30);
    }

    vector<int> a(b);
    for (int i = 0; i < b; ++i) {
        if (mode == 3) {
            a[i] = rnd.next(1, 2);
        } else if (mode == 4) {
            a[i] = rnd.next(1, 10);
        } else if (mode == 5) {
            a[i] = (i == 0 || i + 1 == b) ? rnd.next(8, 25) : rnd.next(1, 4);
        } else {
            a[i] = rnd.next(1, 6);
        }
    }

    long long total = accumulate(a.begin(), a.end(), 0LL);
    int q = rnd.next(1, 20);

    vector<long long> queries;
    queries.push_back(0);
    if (total > 1) queries.push_back(rnd.next(0LL, total - 1));
    queries.push_back(total);
    queries.push_back(1000000000000000000LL);

    while ((int)queries.size() < q) {
        int kind = rnd.next(0, 4);
        if (kind == 0) {
            queries.push_back(rnd.next(0LL, max(0LL, total - 1)));
        } else if (kind == 1) {
            queries.push_back(rnd.next(total, total + 20));
        } else if (kind == 2) {
            queries.push_back(rnd.next(0LL, 100LL));
        } else if (kind == 3) {
            queries.push_back(rnd.next(1000LL, 1000000LL));
        } else {
            queries.push_back(1000000000000000000LL - rnd.next(0LL, 1000LL));
        }
    }
    shuffle(queries.begin(), queries.end());

    println(b, q);
    println(a);
    for (int i = 0; i < q; ++i) {
        println(queries[i]);
    }

    return 0;
}
