#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;

    int mode = rnd.next(0, 4);
    int p = rnd.next(6, 24);

    auto addCase = [&](int b, int m) {
        cases.push_back({b, m});
    };

    addCase(rnd.next(1, 2), rnd.next(1, 12));
    addCase(1, rnd.next(1, 1000));
    addCase(rnd.next(2, 4), rnd.next(1, 1000));
    addCase(rnd.next(25, 50), rnd.next(1, 1000));

    while ((int)cases.size() < p) {
        int b;
        int m;
        if (mode == 0) {
            b = rnd.next(1, 6);
            m = rnd.next(1, 60);
        } else if (mode == 1) {
            b = rnd.next(1, 50);
            m = rnd.next(900, 1000);
        } else if (mode == 2) {
            b = rnd.next(1, 50);
            m = rnd.next(1, 30);
        } else if (mode == 3) {
            b = rnd.next(2, 8);
            m = rnd.next(100, 1000);
        } else {
            b = rnd.next(1, 50);
            m = rnd.next(1, 1000);
        }
        addCase(b, m);
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [b, m] : cases) {
        println(b, m);
    }

    return 0;
}
