#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameters for variability
    int m = rnd.next(1, 10);
    int n = rnd.next(1, 10);
    int Pmax = rnd.next(10, 200);
    int Dmax = rnd.next(1, 20);
    int priceMode = rnd.next(0, 2);
    int dateMode  = rnd.next(0, 2);

    auto genPrice = [&]() {
        if (priceMode == 0)
            return rnd.next(1, Pmax);
        else if (priceMode == 1)
            return rnd.wnext(Pmax, 3) + 1; // skew high
        else
            return rnd.wnext(Pmax, -3) + 1; // skew low
    };
    auto genDate = [&]() {
        if (dateMode == 0)
            return rnd.next(1, Dmax);
        else if (dateMode == 1)
            return rnd.wnext(Dmax, 3) + 1; // skew late
        else
            return rnd.wnext(Dmax, -3) + 1; // skew early
    };

    vector<pair<int,int>> prod(m), cons(n);
    for (int i = 0; i < m; i++) {
        int p = genPrice();
        int d = genDate();
        prod[i] = {p, d};
    }
    for (int j = 0; j < n; j++) {
        int q = genPrice();
        int e = genDate();
        cons[j] = {q, e};
    }

    // Sometimes force no-profit scenario
    if (rnd.next(0, 4) == 0) {
        if (rnd.next(0, 1) == 0) {
            // All q <= min p
            int pmin = prod[0].first;
            for (auto &pr : prod) pmin = min(pmin, pr.first);
            for (auto &cj : cons) {
                cj.first = rnd.next(1, pmin);
            }
        } else {
            // All e <= min d
            int dmin = prod[0].second;
            for (auto &pr : prod) dmin = min(dmin, pr.second);
            for (auto &cj : cons) {
                cj.second = rnd.next(1, dmin);
            }
        }
    }

    // Output
    println(m, n);
    for (auto &pr : prod) println(pr.first, pr.second);
    for (auto &cj : cons) println(cj.first, cj.second);

    return 0;
}
