#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_X = 50000000;

vector<int> makeCubicByDifferences(int n) {
    long long value = rnd.next(0, 10000);
    long long first = rnd.next(0, 2000);
    long long second = rnd.next(0, 200);
    long long third = rnd.next(0, 20);

    vector<int> xs;
    for (int i = 0; i < n; ++i) {
        xs.push_back((int)value);
        value += first;
        first += second;
        second += third;
    }

    return xs;
}

vector<int> makeSimplePolynomial(int n) {
    int mode = rnd.next(0, 2);
    int base = rnd.next(0, 100000);
    int step = rnd.next(0, 20000);
    int quadratic = rnd.next(0, 150);

    vector<int> xs(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            xs[i] = base;
        } else if (mode == 1) {
            xs[i] = min(MAX_X, base + step * i);
        } else {
            xs[i] = min(MAX_X, base + quadratic * (i + 1) * (i + 1));
        }
    }
    return xs;
}

void perturbNonCubic(vector<int>& xs) {
    int pos = rnd.next(4, (int)xs.size() - 1);
    int delta = rnd.next(1, 1000);
    if (xs[pos] + delta <= MAX_X) {
        xs[pos] += delta;
    } else {
        xs[pos] -= delta;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        vector<int> xs;

        if (mode == 0) {
            n = rnd.next(1, 4);
            xs = makeSimplePolynomial(n);
        } else if (mode == 1) {
            n = rnd.any(vector<int>{100, 250, 500});
            xs = makeSimplePolynomial(n);
        } else if (mode <= 3) {
            n = rnd.next(5, 35);
            xs = makeCubicByDifferences(n);
        } else {
            n = rnd.next(5, 35);
            xs = makeCubicByDifferences(n);
            perturbNonCubic(xs);
        }

        printf("%d", n);
        for (int x : xs) {
            printf(" %d", x);
        }
        printf("\n");
    }

    return 0;
}
