#include "testlib.h"
#include <vector>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int t;
    if (mode == 0) {
        t = rnd.next(1, 8);
    } else if (mode == 1) {
        t = rnd.next(9, 30);
    } else if (mode == 2) {
        t = rnd.next(31, 120);
    } else {
        t = rnd.next(1000, 100000);
    }

    vector<pair<int, int>> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int pattern = rnd.next(0, 4);
        int a, b;

        if (pattern == 0) {
            a = 1;
            b = rnd.next(1, 9);
        } else if (pattern == 1) {
            a = 9;
            b = rnd.next(1, 9);
        } else if (pattern == 2) {
            a = rnd.next(1, 9);
            b = rnd.next(1, 9);
        } else if (pattern == 3) {
            a = rnd.next(1, 4);
            b = rnd.next(6, 9);
        } else {
            a = rnd.next(6, 9);
            b = rnd.next(1, 4);
        }

        if (rnd.next(0, 1)) {
            swap(a, b);
        }
        cases.push_back({a, b});
    }

    println(t);
    for (const auto& tc : cases) {
        println(tc.first, tc.second);
    }

    return 0;
}
