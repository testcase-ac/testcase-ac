#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 25);
    vector<pair<int, int>> cases;
    cases.reserve(t);

    vector<int> specialM = {1, 2, 3, 5, 9, 10, 11, 37, 99, 111, 999, 1000};
    vector<int> specialK = {
        1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 16, 20, 36, 99,
        100, 101, 999, 1000, 1000000000
    };

    int mode = rnd.next(0, 5);
    for (int i = 0; i < t; ++i) {
        int k;
        int m;

        if (mode == 0) {
            k = rnd.next(1, 40);
            m = rnd.any(specialM);
        } else if (mode == 1) {
            int base = rnd.next(0, 250000000);
            k = max(1, min(1000000000, base * 4 + rnd.next(1, 4)));
            m = rnd.next(1, 1000);
        } else if (mode == 2) {
            k = rnd.any(specialK);
            m = rnd.next(1, 1000);
        } else if (mode == 3) {
            k = rnd.next(1, 1000000000);
            m = rnd.any(specialM);
        } else if (mode == 4) {
            k = rnd.next(max(1, 1000000000 - 1000), 1000000000);
            m = rnd.next(1, 1000);
        } else {
            k = rnd.next(1, 1000000);
            m = rnd.next(1, 111) * 9;
        }

        cases.emplace_back(k, m);
    }

    shuffle(cases.begin(), cases.end());

    println(t);
    for (const auto& tc : cases) {
        println(tc.first, tc.second);
    }

    return 0;
}
