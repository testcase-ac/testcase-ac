#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int g = rnd.next(6, 15);
    vector<pair<int, int>> cases;
    cases.reserve(g);

    auto addCase = [&](int d, int n) {
        cases.push_back({max(2, min(100, d)), max(2, min(100, n))});
    };

    while ((int)cases.size() < g) {
        int mode = rnd.next(0, 5);

        if (mode == 0) {
            addCase(rnd.next(2, 8), rnd.next(2, 8));
        } else if (mode == 1) {
            int n = rnd.next(2, 10);
            int limit = (n - 1) * (n - 1) + 1;
            addCase(limit, n);
        } else if (mode == 2) {
            int n = rnd.next(2, 10);
            int limit = (n - 1) * (n - 1) + 1;
            addCase(limit + rnd.next(1, 8), n);
        } else if (mode == 3) {
            int d = rnd.next(2, 100);
            int n = rnd.next(80, 100);
            addCase(d, n);
        } else if (mode == 4) {
            int n = rnd.next(2, 4);
            addCase(rnd.next(80, 100), n);
        } else {
            addCase(rnd.next(2, 100), rnd.next(2, 100));
        }
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [d, n] : cases) {
        println(d, n);
    }

    return 0;
}
