#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Triple {
    int a;
    int b;
};

vector<Triple> primitiveTriples() {
    vector<Triple> triples;
    for (int m = 2; m * m <= 999999; ++m) {
        for (int n = 1; n < m; ++n) {
            if (((m - n) % 2 == 0) || gcd(m, n) != 1) continue;
            long long a = 1LL * m * m - 1LL * n * n;
            long long b = 2LL * m * n;
            long long c = 1LL * m * m + 1LL * n * n;
            if (c >= 1000000) continue;
            if (a > b) swap(a, b);
            triples.push_back({(int)a, (int)b});
        }
    }
    return triples;
}

int randomLength(int mode) {
    if (mode == 0) return rnd.next(1, 30);
    if (mode == 1) return rnd.next(1, 2000);
    if (mode == 2) return rnd.next(999000, 999999);
    return rnd.next(1, 999999);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Triple> triples = primitiveTriples();
    vector<int> values;
    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);

    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) values.push_back(randomLength(rnd.next(0, 3)));
    } else if (mode == 1) {
        n = rnd.next(8, 40);
        for (int i = 0; i < n; ++i) values.push_back(randomLength(rnd.next(0, 2)));
    } else if (mode == 2) {
        int pairs = rnd.next(1, 20);
        n = rnd.next(2 * pairs, min(200, 2 * pairs + 40));
        for (int i = 0; i < pairs; ++i) {
            Triple t = rnd.any(triples);
            values.push_back(t.a);
            values.push_back(t.b);
        }
        while ((int)values.size() < n) values.push_back(randomLength(rnd.next(0, 3)));
    } else if (mode == 3) {
        int pairs = rnd.next(1, 50);
        n = rnd.next(2 * pairs, 200);
        Triple t = rnd.any(triples);
        for (int i = 0; i < pairs; ++i) {
            values.push_back(t.a);
            values.push_back(t.b);
        }
        while ((int)values.size() < n) values.push_back(rnd.any(values));
    } else if (mode == 4) {
        n = rnd.next(20, 200);
        for (int i = 0; i < n; ++i) values.push_back(randomLength(2));
        if (n >= 2 && rnd.next(0, 1)) {
            Triple t = rnd.any(triples);
            values[0] = t.a;
            values[1] = t.b;
        }
    } else {
        int pairs = rnd.next(1, 80);
        n = min(200, 2 * pairs + rnd.next(0, 40));
        for (int i = 0; i < pairs && (int)values.size() + 1 < n; ++i) {
            Triple t = rnd.any(triples);
            values.push_back(t.a);
            values.push_back(t.b);
        }
        while ((int)values.size() < n) values.push_back(randomLength(rnd.next(0, 3)));
    }

    shuffle(values.begin(), values.end());
    println((int)values.size());
    println(values);
    return 0;
}
