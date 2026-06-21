#include "testlib.h"

#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

const __int128_t LIMIT = numeric_limits<long long>::max();

struct Query {
    int p;
    int r;
    int c;
};

__int128_t multiplyCapped(__int128_t a, long long b) {
    __int128_t product = a * b;
    if (product > LIMIT) {
        return LIMIT + 1;
    }
    return product;
}

__int128_t binomCapped(int n, int k) {
    k = min(k, n - k);
    __int128_t result = 1;
    for (int i = 1; i <= k; ++i) {
        __int128_t next = result * (n - i + 1) / i;
        if (next > LIMIT) {
            return LIMIT + 1;
        }
        result = next;
    }
    return result;
}

bool fitsSigned64(int p, int r, int c) {
    __int128_t value = binomCapped(r, c);
    if (value > LIMIT) {
        return false;
    }

    for (int i = 0; i < r - c; ++i) {
        value = multiplyCapped(value, p);
        if (value > LIMIT) {
            return false;
        }
    }
    return true;
}

Query makeValid(int p, int r, int c) {
    ensure(fitsSigned64(p, r, c));
    return {p, r, c};
}

Query randomValid() {
    for (int tries = 0; tries < 1000; ++tries) {
        int mode = rnd.next(0, 6);
        int p;
        int r;
        int c;

        if (mode == 0) {
            p = rnd.next(1, 100000);
            r = rnd.next(0, 100000);
            c = r;
        } else if (mode == 1) {
            p = rnd.next(1, 100000);
            r = rnd.next(1, 100000);
            c = r - 1;
        } else if (mode == 2) {
            p = rnd.any(vector<int>{1, 2, 3, 5, 10, 100, 1000, 100000});
            r = rnd.next(0, 12);
            c = rnd.next(0, r);
        } else if (mode == 3) {
            p = rnd.next(1, 30);
            r = rnd.next(20, 70);
            c = rnd.next(max(0, r - 12), r);
        } else if (mode == 4) {
            p = rnd.next(1, 100000);
            r = rnd.next(99900, 100000);
            c = rnd.next(max(0, r - 2), r);
        } else if (mode == 5) {
            p = rnd.next(1, 20);
            r = rnd.next(0, 45);
            c = rnd.next(0, min(r, 8));
        } else {
            p = rnd.next(1, 100000);
            r = rnd.next(0, 100000);
            int gap = rnd.next(0, 6);
            c = max(0, r - gap);
        }

        if (fitsSigned64(p, r, c)) {
            return {p, r, c};
        }
    }

    int r = rnd.next(0, 100000);
    return makeValid(1, r, rnd.next(0, r));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Query> queries;
    queries.push_back(makeValid(1, 0, 0));
    queries.push_back(makeValid(100000, 1, 0));
    queries.push_back(makeValid(100000, 100000, 100000));
    queries.push_back(makeValid(200, 100000, 99998));

    int k = rnd.next(8, 24);
    while ((int)queries.size() < k) {
        queries.push_back(randomValid());
    }
    shuffle(queries.begin(), queries.end());

    println((int)queries.size());
    for (int i = 0; i < (int)queries.size(); ++i) {
        println(i + 1, queries[i].p, queries[i].r, queries[i].c);
    }

    return 0;
}
