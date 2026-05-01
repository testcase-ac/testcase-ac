#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Pizza {
    int D;
    int P;
};

bool ratioEqual(const Pizza &a, const Pizza &b) {
    // Compare D^2 / P using cross multiplication: a.D^2 * b.P == b.D^2 * a.P
    return 1LL * a.D * a.D * b.P == 1LL * b.D * b.D * a.P;
}

bool ratioUnique(int D, int P, const vector<Pizza> &pizzas) {
    Pizza cur{D, P};
    for (const auto &pz : pizzas) {
        if (ratioEqual(cur, pz)) return false;
    }
    return true;
}

int generatePrice(int D, const vector<Pizza> &pizzas, int mode, double costFactor) {
    if (mode == 0) {
        // Pure random prices, then fallback.
        for (int tries = 0; tries < 200; ++tries) {
            int P = rnd.next(1, 100);
            if (ratioUnique(D, P, pizzas)) return P;
        }
        for (int P = 1; P <= 100; ++P) {
            if (ratioUnique(D, P, pizzas)) return P;
        }
    } else {
        int base = (int) ::round((double)D * (double)D * costFactor);
        if (base < 1) base = 1;
        if (base > 100) base = 100;

        vector<int> candidates;
        candidates.push_back(base);
        for (int delta = -2; delta <= 2; ++delta) {
            if (delta == 0) continue;
            int v = base + delta;
            if (v >= 1 && v <= 100) candidates.push_back(v);
        }
        candidates.push_back(rnd.next(1, 100));
        shuffle(candidates.begin(), candidates.end());

        for (int P : candidates) {
            if (ratioUnique(D, P, pizzas)) return P;
        }
        for (int P = 1; P <= 100; ++P) {
            if (ratioUnique(D, P, pizzas)) return P;
        }
    }
    // Guaranteed to find something by pigeonhole principle.
    return 1;
}

vector<Pizza> generateSpecialMenu() {
    // Two pizzas where the smaller diameter is the better value.
    vector<Pizza> pizzas;

    int D1 = rnd.next(6, 10);
    int D2 = rnd.next(D1 + 1, min(20, D1 + 5));
    int P1 = rnd.next(1, 5);

    // Ensure smaller pizza (D1) has better value:
    // D1^2 / P1 > D2^2 / P2  =>  P2 > D2^2 * P1 / D1^2
    long long numer = 1LL * D2 * D2 * P1;
    long long denom = 1LL * D1 * D1;
    int threshold = (int)(numer / denom); // floor
    int lowP2 = threshold + 1;
    lowP2 = max(lowP2, P1 + 1);
    if (lowP2 < 1) lowP2 = 1;
    if (lowP2 > 100) lowP2 = 100;
    int P2 = rnd.next(lowP2, 100);

    pizzas.push_back(Pizza{D1, P1});
    pizzas.push_back(Pizza{D2, P2});
    return pizzas;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 4);
    int specialIdx = rnd.next(1, T); // one menu with small pizza best

    for (int menu = 1; menu <= T; ++menu) {
        vector<Pizza> pizzas;

        if (menu == specialIdx) {
            pizzas = generateSpecialMenu();
        } else {
            int mode = rnd.next(0, 2); // 0: very small/random, 1-2: structured
            double costFactor = 0.0;
            int N;

            if (mode == 0) {
                N = rnd.next(1, 3);
            } else if (mode == 1) {
                N = rnd.next(3, 7);
                costFactor = 0.02 + 0.05 * rnd.next(); // [0.02, 0.07)
            } else {
                N = rnd.next(5, 10);
                costFactor = 0.03 + 0.04 * rnd.next(); // [0.03, 0.07)
            }

            int maxD;
            if (mode == 0) maxD = rnd.next(6, 12);
            else if (mode == 1) maxD = rnd.next(15, 30);
            else maxD = 36;

            maxD = max(maxD, N);
            if (maxD > 36) maxD = 36;

            vector<int> candD;
            for (int d = 1; d <= maxD; ++d) candD.push_back(d);
            shuffle(candD.begin(), candD.end());
            candD.resize(N);

            pizzas.clear();
            for (int D : candD) {
                int P = generatePrice(D, pizzas, mode, costFactor);
                pizzas.push_back(Pizza{D, P});
            }
        }

        // Shuffle pizzas within the menu for variability.
        shuffle(pizzas.begin(), pizzas.end());

        println((int)pizzas.size());
        for (const auto &pz : pizzas) {
            println(pz.D, pz.P);
        }
    }

    println(0);
    return 0;
}
