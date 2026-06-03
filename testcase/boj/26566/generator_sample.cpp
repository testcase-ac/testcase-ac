#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 20);
    vector<tuple<int, int, int, int>> cases;
    cases.reserve(n);

    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(0, 5);
        int a1, p1, r1, p2;

        if (mode == 0) {
            a1 = rnd.next(1, 12);
            p1 = rnd.next(1, 12);
            r1 = rnd.next(1, 8);
            p2 = rnd.next(1, 20);
        } else if (mode == 1) {
            a1 = rnd.any(vector<int>{1, 2, 999, 1000});
            p1 = rnd.any(vector<int>{1, 2, 999, 1000});
            r1 = rnd.any(vector<int>{1, 2, 31, 32, 999, 1000});
            p2 = rnd.any(vector<int>{1, 2, 999, 1000});
        } else if (mode == 2) {
            a1 = rnd.next(700, 1000);
            p1 = rnd.next(1, 5);
            r1 = rnd.next(1, 6);
            p2 = rnd.next(500, 1000);
        } else if (mode == 3) {
            a1 = rnd.next(1, 25);
            p1 = rnd.next(500, 1000);
            r1 = rnd.next(15, 35);
            p2 = rnd.next(1, 10);
        } else if (mode == 4) {
            int base = rnd.next(1, 30);
            a1 = rnd.next(max(1, base - 3), min(1000, base + 3));
            p1 = rnd.next(1, 30);
            r1 = rnd.next(1, 20);
            p2 = rnd.next(1, 60);
        } else {
            a1 = rnd.next(1, 1000);
            p1 = rnd.next(1, 1000);
            r1 = rnd.next(1, 1000);
            p2 = rnd.next(1, 1000);
        }

        cases.emplace_back(a1, p1, r1, p2);
    }

    shuffle(cases.begin(), cases.end());

    println(n);
    for (const auto& [a1, p1, r1, p2] : cases) {
        println(a1, p1);
        println(r1, p2);
    }

    return 0;
}
