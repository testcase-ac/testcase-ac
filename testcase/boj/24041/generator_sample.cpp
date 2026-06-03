#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

struct Ingredient {
    long long s;
    long long l;
    int o;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(5, 12);
    } else if (mode == 2) {
        n = rnd.next(12, 35);
    } else if (mode == 3) {
        n = rnd.next(2, 10);
    } else if (mode == 4) {
        n = rnd.next(8, 24);
    } else {
        n = rnd.next(20, 60);
    }

    vector<Ingredient> ingredients(n);
    long long sumS = 0;
    for (int i = 0; i < n; ++i) {
        long long s;
        if (mode == 3) {
            s = rnd.next(1LL, 3LL);
        } else if (mode == 4) {
            s = rnd.next(1LL, 1000000LL);
        } else {
            s = rnd.next(1LL, 100LL);
        }

        long long l;
        if (mode == 0) {
            l = rnd.next(1LL, 5LL);
        } else if (mode == 1) {
            l = rnd.next(1LL, 30LL);
        } else if (mode == 2) {
            l = (i % 3 == 0) ? rnd.next(1LL, 4LL) : rnd.next(20LL, 100LL);
        } else if (mode == 3) {
            l = rnd.next(999999990LL, 1000000000LL);
        } else if (mode == 4) {
            l = rnd.next(1LL, 1000000000LL);
        } else {
            l = rnd.next(1LL, 200LL);
        }

        int o;
        if (mode == 0) {
            o = rnd.next(0, 1);
        } else if (mode == 5) {
            o = (i % 4 != 0);
        } else {
            o = rnd.next() < 0.65 ? 1 : 0;
        }

        ingredients[i] = {s, l, o};
        sumS += s;
    }

    if (mode == 2) {
        sort(ingredients.begin(), ingredients.end(), [](const Ingredient& a, const Ingredient& b) {
            if (a.l != b.l) return a.l < b.l;
            return a.s > b.s;
        });
    } else {
        shuffle(ingredients.begin(), ingredients.end());
    }

    int removable = 0;
    for (const auto& ingredient : ingredients) removable += ingredient.o;

    int k;
    if (n == 1) {
        k = 0;
    } else if (mode == 0) {
        k = rnd.next(0, n - 1);
    } else if (mode == 5) {
        k = min(n - 1, max(0, removable - rnd.next(0, min(removable, 3))));
    } else {
        k = rnd.next(0, min(n - 1, max(0, removable + 2)));
    }

    long long slack;
    if (mode == 4) {
        slack = rnd.next(0LL, max(0LL, 1000000000LL - sumS));
    } else if (rnd.next(0, 3) == 0) {
        slack = 0;
    } else {
        slack = rnd.next(0LL, min(1000000LL, 1000000000LL - sumS));
    }
    long long g = sumS + slack;

    println(n, g, k);
    for (const auto& ingredient : ingredients) {
        println(ingredient.s, ingredient.l, ingredient.o);
    }

    return 0;
}
