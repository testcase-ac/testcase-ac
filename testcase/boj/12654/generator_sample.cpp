#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int choosePackSize(int c) {
    int mode = rnd.next(0, 6);
    if (mode == 0) return 1;
    if (mode == 1) return c;
    if (mode == 2) return max(1, c - 1);
    if (mode == 3) return (c + 1) / 2;
    if (mode == 4) return rnd.next(1, min(c, 5));
    if (mode == 5) return rnd.next(max(1, c - 5), c);
    return rnd.next(1, c);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;

    cases.push_back({1, 1});
    cases.push_back({2, 1});
    cases.push_back({2, 2});
    cases.push_back({40, 1});
    cases.push_back({40, rnd.next(18, 22)});
    cases.push_back({40, 39});
    cases.push_back({40, 40});

    int extra = rnd.next(8, 18);
    for (int i = 0; i < extra; ++i) {
        int cMode = rnd.next(0, 4);
        int c;
        if (cMode == 0) {
            c = rnd.next(1, 6);
        } else if (cMode == 1) {
            c = rnd.next(7, 15);
        } else if (cMode == 2) {
            c = rnd.next(16, 39);
        } else {
            c = 40;
        }
        cases.push_back({c, choosePackSize(c)});
    }

    shuffle(cases.begin(), cases.end());

    println(static_cast<int>(cases.size()));
    for (auto [c, n] : cases) {
        println(c, n);
    }

    return 0;
}
