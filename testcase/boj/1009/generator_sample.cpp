#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int T = rnd.next(8, 35);
    vector<pair<int, int>> cases;

    auto addCase = [&](int a, int b) {
        cases.push_back({a, b});
    };

    if (mode == 0) {
        for (int last = 0; last <= 9; ++last) {
            int a = last == 0 ? 10 * rnd.next(1, 9) : last + 10 * rnd.next(0, 9);
            if (a > 99) a -= 10;
            int b = rnd.next(1, 12);
            addCase(a, b);
        }
    } else if (mode == 1) {
        vector<int> bases = {1, 2, 4, 5, 6, 9, 10, 11, 49, 50, 99};
        vector<int> exponents = {1, 2, 3, 4, 999998, 999999};
        for (int a : bases) {
            addCase(a, rnd.any(exponents));
        }
    } else if (mode == 2) {
        for (int i = 0; i < T; ++i) {
            int last = rnd.next(0, 9);
            int a = last == 0 ? 10 * rnd.next(1, 9) : last + 10 * rnd.next(0, 9);
            if (a > 99) a -= 10;
            int periodProbe = rnd.next(0, 7);
            int b = 1 + periodProbe + 4 * rnd.next(0, 12);
            addCase(a, b);
        }
    } else {
        for (int i = 0; i < T; ++i) {
            int a = rnd.next(1, 99);
            int b = rnd.next(1, 999999);
            addCase(a, b);
        }
    }

    if (mode != 3) {
        while ((int)cases.size() < T) {
            addCase(rnd.next(1, 99), rnd.next(1, 999999));
        }
    }
    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [a, b] : cases) {
        println(a, b);
    }

    return 0;
}
