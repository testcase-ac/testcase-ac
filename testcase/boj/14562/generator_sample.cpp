#include "testlib.h"
#include <utility>
#include <vector>

using namespace std;

pair<int, int> randomCase(int mode) {
    int s, t;

    if (mode == 0) {
        s = rnd.next(1, 99);
        t = rnd.next(s + 1, min(100, s + 5));
    } else if (mode == 1) {
        s = rnd.next(1, 15);
        t = rnd.next(max(s + 1, 70), 100);
    } else if (mode == 2) {
        s = rnd.next(80, 99);
        t = rnd.next(s + 1, 100);
    } else if (mode == 3) {
        s = rnd.next(1, 6);
        t = rnd.next(s + 1, min(100, s + rnd.next(10, 35)));
    } else {
        s = rnd.next(1, 99);
        t = rnd.next(s + 1, 100);
    }

    return {s, t};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int c = rnd.next(1, 100);
    vector<pair<int, int>> cases;
    cases.reserve(c);

    for (int i = 0; i < c; ++i) {
        int mode = rnd.next(0, 4);
        cases.push_back(randomCase(mode));
    }

    println(c);
    for (auto [s, t] : cases) {
        println(s, t);
    }

    return 0;
}
