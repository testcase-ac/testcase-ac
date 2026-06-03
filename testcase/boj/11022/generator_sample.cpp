#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int T = rnd.next(1, 20);
    vector<pair<int, int>> tests;
    tests.reserve(T);

    for (int i = 0; i < T; ++i) {
        int a = rnd.next(1, 9);
        int b = rnd.next(1, 9);

        if (mode == 1 && i % 3 == 0) {
            a = rnd.any(vector<int>{1, 9});
            b = rnd.next(1, 9);
        } else if (mode == 2 && i % 3 == 1) {
            a = rnd.next(1, 9);
            b = rnd.any(vector<int>{1, 9});
        } else if (mode == 3) {
            a = rnd.next(1, 4);
            b = rnd.next(6, 9);
            if (rnd.next(0, 1) == 1) swap(a, b);
        }

        tests.emplace_back(a, b);
    }

    println(T);
    for (auto [a, b] : tests) {
        println(a, b);
    }

    return 0;
}
