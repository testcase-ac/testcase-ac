#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 10);
    vector<pair<int, int>> ingredients;
    ingredients.reserve(n);

    auto addPair = [&](int required, int available) {
        ingredients.push_back({required, available});
    };

    if (mode == 0) {
        int required = rnd.next(1, 10000);
        int available = rnd.next(1, required);
        addPair(required, available);
        n = 1;
    } else if (mode == 1) {
        int cakes = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            int required = rnd.next(1, max(1, 10000 / max(1, cakes + 1)));
            int extra = rnd.next(0, required - 1);
            int available = required * cakes + extra;
            addPair(required, max(1, min(10000, available)));
        }
    } else if (mode == 2) {
        int limitingCakes = rnd.next(0, 100);
        for (int i = 0; i < n; ++i) {
            int required = rnd.next(1, 100);
            int cakes = limitingCakes + rnd.next(0, 10);
            int available = min(10000, required * cakes + rnd.next(0, required - 1));
            addPair(required, max(1, available));
        }
        int idx = rnd.next(n);
        int required = rnd.next(1, 100);
        int available = min(10000, required * limitingCakes + rnd.next(0, required - 1));
        ingredients[idx] = {required, max(1, available)};
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int required = rnd.any(vector<int>{1, 2, 3, 7, 99, 100, 9999, 10000});
            int available = rnd.next(1, 10000);
            addPair(required, available);
        }
    } else if (mode == 4) {
        int base = rnd.next(1, 10000);
        for (int i = 0; i < n; ++i) {
            int required = rnd.next(1, base);
            int available = rnd.next(base, 10000);
            addPair(required, available);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int required = rnd.next(1, 10000);
            int available = rnd.next(1, 10000);
            addPair(required, available);
        }
    }

    shuffle(ingredients.begin(), ingredients.end());

    println(static_cast<int>(ingredients.size()));
    for (const auto& ingredient : ingredients) {
        println(ingredient.first, ingredient.second);
    }

    return 0;
}
