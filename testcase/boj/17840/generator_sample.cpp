#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long pickNearLimit() {
    const long long limit = 1000000000000000LL;
    return limit - rnd.next(0, 200000);
}

long long pickQuery(int mode) {
    if (mode == 0) return rnd.next(1, 80);
    if (mode == 1) return rnd.next(1, 5000);
    if (mode == 2) return pickNearLimit();
    if (mode == 3) {
        vector<long long> edges = {
            1LL,
            2LL,
            9LL,
            10LL,
            11LL,
            99LL,
            100LL,
            101LL,
            999999999999999LL,
            1000000000000000LL,
        };
        return rnd.any(edges);
    }
    if (rnd.next(0, 3) == 0) return pickNearLimit();
    return rnd.next(1, 2000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> specialM = {2, 3, 4, 5, 8, 10, 11, 16, 37, 99, 100, 997, 1000};

    int q;
    int m;
    if (mode == 0) {
        q = rnd.next(1, 8);
        m = rnd.next(2, 12);
    } else if (mode == 1) {
        q = rnd.next(8, 20);
        m = rnd.any(specialM);
    } else if (mode == 2) {
        q = rnd.next(3, 12);
        m = rnd.next(900, 1000);
    } else if (mode == 3) {
        q = rnd.next(6, 16);
        m = rnd.any(specialM);
    } else {
        q = rnd.next(12, 30);
        m = rnd.next(2, 1000);
    }

    vector<long long> queries;
    for (int i = 0; i < q; ++i) queries.push_back(pickQuery(mode));

    if (mode == 3) {
        shuffle(queries.begin(), queries.end());
    } else if (rnd.next(0, 1)) {
        sort(queries.begin(), queries.end());
    }

    println(q, m);
    for (long long n : queries) println(n);

    return 0;
}
