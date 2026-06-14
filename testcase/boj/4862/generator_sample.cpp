#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<tuple<int, int, int>> cases;

    auto addCase = [&](int b, int i, int n) {
        cases.emplace_back(b, i, n);
    };

    addCase(1, 1, rnd.next(1, 7));
    addCase(1, rnd.next(2, 100), 7);
    addCase(100, 1, rnd.next(1, 7));
    addCase(100, rnd.next(2, 100), 7);
    addCase(rnd.any(vector<int>{2, 3, 7, 9}), 1, rnd.next(1, 7));
    addCase(rnd.any(vector<int>{2, 3, 7, 9}), 100, 7);

    int extra = rnd.next(8, 18);
    for (int tc = 0; tc < extra; ++tc) {
        int mode = rnd.next(0, 5);
        int b;
        int i;
        int n;

        if (mode == 0) {
            b = rnd.any(vector<int>{2, 4, 8, 16, 32, 64});
            i = rnd.any(vector<int>{2, 3, 4, 5, 10, 100});
            n = rnd.any(vector<int>{1, 2, 6, 7});
        } else if (mode == 1) {
            b = rnd.any(vector<int>{5, 10, 20, 25, 50, 75, 100});
            i = rnd.next(1, 100);
            n = rnd.next(1, 7);
        } else if (mode == 2) {
            b = rnd.any(vector<int>{3, 7, 9, 11, 13, 17, 19, 21, 37, 99});
            i = rnd.next(1, 100);
            n = rnd.any(vector<int>{1, 3, 5, 7});
        } else if (mode == 3) {
            b = rnd.next(1, 100);
            i = rnd.any(vector<int>{1, 2, 3, 4, 99, 100});
            n = rnd.next(1, 7);
        } else if (mode == 4) {
            b = rnd.next(90, 100);
            i = rnd.next(90, 100);
            n = rnd.next(6, 7);
        } else {
            b = rnd.next(1, 100);
            i = rnd.next(1, 100);
            n = rnd.next(1, 7);
        }

        addCase(b, i, n);
    }

    shuffle(cases.begin(), cases.end());
    for (auto [b, i, n] : cases) {
        println(b);
        println(i);
        println(n);
    }
    println(0);

    return 0;
}
