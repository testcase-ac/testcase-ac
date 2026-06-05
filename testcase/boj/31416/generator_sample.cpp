#include "testlib.h"
#include <utility>
#include <vector>

using namespace std;

using Case = pair<pair<int, int>, pair<int, int>>;

Case makeCase(int mode) {
    int ta = 1, tb = 1, va = 1, vb = 1;

    if (mode == 0) {
        ta = rnd.next(1, 5);
        tb = rnd.next(1, 5);
        va = rnd.next(1, 8);
        vb = rnd.next(1, 8);
    } else if (mode == 1) {
        ta = rnd.next(80, 100);
        tb = rnd.next(1, 8);
        va = rnd.next(1, 12);
        vb = rnd.next(70, 100);
    } else if (mode == 2) {
        ta = rnd.next(1, 8);
        tb = rnd.next(80, 100);
        va = rnd.next(70, 100);
        vb = rnd.next(1, 12);
    } else if (mode == 3) {
        int t = rnd.next(1, 100);
        ta = t;
        tb = t;
        va = rnd.next(1, 100);
        vb = rnd.next(1, 100);
    } else if (mode == 4) {
        ta = rnd.next(1, 100);
        tb = rnd.next(1, 100);
        int total = rnd.next(2, 100);
        va = rnd.next(1, total - 1);
        vb = total - va;
    } else if (mode == 5) {
        ta = rnd.any(vector<int>{1, 2, 99, 100});
        tb = rnd.any(vector<int>{1, 2, 99, 100});
        va = rnd.any(vector<int>{1, 2, 99, 100});
        vb = rnd.any(vector<int>{1, 2, 99, 100});
    } else {
        ta = rnd.next(1, 100);
        tb = rnd.next(1, 100);
        va = rnd.next(1, 100);
        vb = rnd.next(1, 100);
    }

    return {{ta, tb}, {va, vb}};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int q = rnd.next(1, 40);
    vector<Case> cases;
    cases.reserve(q);

    for (int i = 0; i < q; ++i) {
        int mode = rnd.next(0, 6);
        cases.push_back(makeCase(mode));
    }

    println(q);
    for (const Case& tc : cases) {
        println(tc.first.first, tc.first.second, tc.second.first, tc.second.second);
    }

    return 0;
}
