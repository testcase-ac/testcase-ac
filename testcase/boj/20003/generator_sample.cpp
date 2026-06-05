#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<pair<int, int>> fractions;

    if (mode == 0) {
        n = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            int value = rnd.next(1, 40);
            fractions.push_back({value, 1});
        }
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        int denominator = rnd.next(2, 40);
        for (int i = 0; i < n; ++i) {
            fractions.push_back({rnd.next(1, 40), denominator});
        }
    } else if (mode == 2) {
        n = rnd.next(3, 10);
        for (int i = 0; i < n; ++i) {
            int baseA = rnd.next(1, 8);
            int baseB = rnd.next(1, 8);
            int factor = rnd.next(1, 40 / max(baseA, baseB));
            fractions.push_back({baseA * factor, baseB * factor});
        }
    } else if (mode == 3) {
        vector<int> denominators = {24, 25, 27, 28, 32, 35, 36, 40};
        shuffle(denominators.begin(), denominators.end());
        n = rnd.next(4, 8);
        for (int i = 0; i < n; ++i) {
            fractions.push_back({rnd.next(1, 40), denominators[i]});
        }
    } else if (mode == 4) {
        n = 50;
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(1, 40);
            int b = rnd.next(1, 40);
            if (rnd.next(0, 3) == 0) {
                a = rnd.any(vector<int>{1, 39, 40});
            }
            if (rnd.next(0, 3) == 0) {
                b = rnd.any(vector<int>{1, 39, 40});
            }
            fractions.push_back({a, b});
        }
    } else {
        n = rnd.next(5, 14);
        for (int i = 0; i < n; ++i) {
            int upper = rnd.next(2, 40);
            fractions.push_back({rnd.next(1, upper), rnd.next(1, upper)});
        }
    }

    shuffle(fractions.begin(), fractions.end());

    println(n);
    for (auto [a, b] : fractions) {
        println(a, b);
    }

    return 0;
}
