#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long kMaxX = 10000000000000LL;
    int mode = rnd.next(0, 5);

    long long x;
    if (mode == 5) {
        x = kMaxX;
    } else if (mode == 4) {
        x = rnd.next(1LL, 1000000LL);
    } else {
        x = rnd.next(1LL, 30LL);
    }

    int n = rnd.next(1, 18);
    int m = rnd.next(1, 18);
    vector<long long> a;
    a.reserve(n);

    auto smallStep = [&]() {
        long long limit = min<long long>(x, max(1LL, x / rnd.next(2, 8)));
        return rnd.next(-limit, limit);
    };

    for (int i = 0; i < n; ++i) {
        long long value = 0;
        if (mode == 0) {
            value = smallStep();
        } else if (mode == 1) {
            value = (i % 2 == 0 ? x : -x);
        } else if (mode == 2) {
            value = rnd.any(vector<long long>{-x, -1, 0, 1, x});
        } else if (mode == 3) {
            long long limit = min<long long>(x, 5);
            value = rnd.next(-limit, limit);
        } else if (mode == 4) {
            value = rnd.next(0, 3) == 0 ? rnd.any(vector<long long>{-x, x}) : smallStep();
        } else {
            value = rnd.next(0, 1) ? x : -x;
        }
        a.push_back(value);
    }

    vector<long long> queries;
    queries.push_back(0);
    if (x > 0) queries.push_back(x);
    if (x >= 2) queries.push_back(1);
    if (x >= 2) queries.push_back(x - 1);
    if (x >= 3) queries.push_back(x / 2);
    while ((int)queries.size() < m) {
        if (rnd.next(0, 3) == 0) {
            queries.push_back(rnd.any(vector<long long>{0, x}));
        } else {
            queries.push_back(rnd.next(0LL, x));
        }
    }
    shuffle(queries.begin(), queries.end());
    queries.resize(m);

    println(x, n);
    println(a);
    println(m);
    for (long long y : queries) {
        println(y);
    }

    return 0;
}
