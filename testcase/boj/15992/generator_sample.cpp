#include "testlib.h"
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t = 0;
    if (mode == 0) {
        t = rnd.next(1, 8);
    } else if (mode == 1) {
        t = rnd.next(8, 20);
    } else {
        t = rnd.next(20, 45);
    }

    vector<pair<int, int>> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int n, m;
        int kind = rnd.next(0, 8);

        if (kind == 0) {
            n = rnd.next(1, 12);
            m = rnd.next(1, n);
        } else if (kind == 1) {
            n = rnd.next(1, 1000);
            m = n;
        } else if (kind == 2) {
            n = rnd.next(2, 1000);
            m = rnd.next(1, n - 1);
        } else if (kind == 3) {
            m = rnd.next(1, 333);
            n = rnd.next(3 * m + 1, 1000);
        } else if (kind == 4) {
            m = rnd.next(1, 334);
            n = rnd.next(m, min(1000, 3 * m));
        } else if (kind == 5) {
            n = rnd.next(980, 1000);
            m = rnd.next(1, n);
        } else if (kind == 6) {
            n = rnd.next(1, 1000);
            m = rnd.next(max(1, (n + 2) / 3), n);
        } else {
            n = rnd.next(1, 1000);
            m = rnd.next(1, n);
        }

        cases.push_back({n, m});
    }

    println((int)cases.size());
    for (const auto& testCase : cases) {
        println(testCase.first, testCase.second);
    }

    return 0;
}
