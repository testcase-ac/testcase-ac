#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 80);
    vector<pair<int, int>> cases;
    cases.reserve(t);

    auto addCase = [&](int n, int k) {
        cases.emplace_back(n, k);
    };

    addCase(1, rnd.next(0, 1));
    addCase(1000, rnd.next(0, 1) ? 0 : 1000);
    addCase(1000, rnd.next(1, 999));

    while ((int)cases.size() < t) {
        int mode = rnd.next(8);
        int n = 1;
        int k = 0;

        if (mode == 0) {
            n = rnd.next(1, 1000);
            k = 0;
        } else if (mode == 1) {
            n = rnd.next(1, 1000);
            k = n;
        } else if (mode == 2) {
            n = rnd.next(2, 1000);
            k = 1;
        } else if (mode == 3) {
            n = rnd.next(2, 1000);
            k = n - 1;
        } else if (mode == 4) {
            n = rnd.next(2, 30);
            k = rnd.next(0, n);
        } else if (mode == 5) {
            n = rnd.next(900, 1000);
            k = rnd.next(0, n);
        } else if (mode == 6) {
            n = rnd.next(2, 1000);
            int mid = n / 2;
            k = rnd.next(max(0, mid - 3), min(n, mid + 3));
        } else {
            n = rnd.next(2, 1000);
            k = rnd.next(0, n);
            if (rnd.next(2)) k = n - k;
        }

        addCase(n, k);
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [n, k] : cases) {
        println(n, k);
    }

    return 0;
}
