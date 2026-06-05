#include "testlib.h"
#include <numeric>
#include <vector>
using namespace std;

int chooseKWithGcd(int n, int g) {
    int reduced = n / g;
    vector<int> candidates;
    for (int x = 1; x <= reduced; ++x) {
        if (gcd(x, reduced) == 1) {
            candidates.push_back(g * x);
        }
    }
    return rnd.any(candidates);
}

vector<int> sortablePermutation(int n, int g) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    for (int start = 0; start < g; ++start) {
        vector<int> positions;
        for (int i = start; i < n; i += g) {
            positions.push_back(i);
        }
        vector<int> values;
        for (int pos : positions) {
            values.push_back(a[pos]);
        }
        shuffle(values.begin(), values.end());
        for (int i = 0; i < int(positions.size()); ++i) {
            a[positions[i]] = values[i];
        }
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 5) {
        n = rnd.next(31, 80);
    } else {
        n = rnd.next(2, 30);
    }

    vector<int> divisors;
    for (int d = 1; d <= n; ++d) {
        if (n % d == 0) {
            divisors.push_back(d);
        }
    }

    int g = 1;
    if (mode == 1) {
        g = 1;
    } else if (mode == 2) {
        g = n;
    } else {
        g = rnd.any(divisors);
    }

    int k = chooseKWithGcd(n, g);
    vector<int> a;

    if (mode == 0 || mode == 2) {
        a.resize(n);
        iota(a.begin(), a.end(), 0);
    } else if (mode == 1 || mode == 3) {
        a = sortablePermutation(n, g);
    } else {
        a = sortablePermutation(n, g);
        if (g > 1) {
            int first = rnd.next(0, n - 1);
            vector<int> differentClass;
            for (int i = 0; i < n; ++i) {
                if (i % g != first % g) {
                    differentClass.push_back(i);
                }
            }
            swap(a[first], a[rnd.any(differentClass)]);
        } else {
            shuffle(a.begin(), a.end());
        }
    }

    println(n, k);
    println(a);
    return 0;
}
