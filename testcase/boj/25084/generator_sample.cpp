#include "testlib.h"

#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<tuple<int, int, int>> cases;

    auto addCase = [&](int r, int a, int b) {
        cases.emplace_back(r, a, b);
    };

    addCase(1, 1, 2);
    addCase(100000, 500, 1000);
    addCase(rnd.next(1, 20), rnd.next(1, 8), 1000);
    addCase(rnd.next(90000, 100000), 1, rnd.next(2, 5));
    addCase(rnd.next(1, 100000), rnd.next(450, 500), 1000);

    int targetT = rnd.next(12, 30);
    while ((int)cases.size() < targetT) {
        int mode = rnd.next(0, 5);
        int r;
        int a;
        int b;

        if (mode == 0) {
            r = rnd.next(1, 25);
            a = rnd.next(1, 10);
            b = rnd.next(2 * a, min(1000, 2 * a + 20));
        } else if (mode == 1) {
            r = rnd.next(1, 100000);
            a = rnd.next(1, 500);
            b = rnd.next(2 * a, 1000);
        } else if (mode == 2) {
            r = rnd.next(95000, 100000);
            a = rnd.next(1, 500);
            b = 2 * a;
        } else if (mode == 3) {
            r = rnd.next(1, 100000);
            a = rnd.next(1, 5);
            b = rnd.next(900, 1000);
        } else if (mode == 4) {
            r = rnd.next(1, 100);
            a = rnd.next(490, 500);
            b = rnd.next(2 * a, 1000);
        } else {
            r = rnd.next(1, 100000);
            a = rnd.next(1, 500);
            b = rnd.next(2 * a, min(1000, 2 * a + 5));
        }

        addCase(r, a, b);
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [r, a, b] : cases) {
        println(r, a, b);
    }

    return 0;
}
