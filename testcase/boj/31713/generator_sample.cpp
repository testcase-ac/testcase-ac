#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

pair<int, int> makeCase(int mode) {
    if (mode == 0) {
        int a = rnd.next(0, 20);
        int b = (a == 0 ? 0 : rnd.next(3 * a, 4 * a));
        return {a, b};
    }

    if (mode == 1) {
        int a = rnd.next(1, 25);
        int b = rnd.next(0, 3 * a - 1);
        return {a, b};
    }

    if (mode == 2) {
        int a = rnd.next(0, 20);
        int low = min(1000, 4 * a + 1);
        int b = rnd.next(low, 1000);
        return {a, b};
    }

    if (mode == 3) {
        int a = rnd.next(0, 8);
        int b = rnd.any(vector<int>{0, 1, 2, 3, 4, 5, 7, 11, 16, 999, 1000});
        return {a, b};
    }

    int a = rnd.next(900, 1000);
    int b = rnd.next(900, 1000);
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 40);
    vector<pair<int, int>> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 4);
        cases.push_back(makeCase(mode));
    }

    println(t);
    for (auto [a, b] : cases) {
        println(a, b);
    }

    return 0;
}
