#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    vector<pair<int, int>> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 5);
        int n;
        int k;

        if (mode == 0) {
            n = rnd.next(1, 8);
            k = rnd.next(1, n);
        } else if (mode == 1) {
            n = rnd.next(1, 1000);
            k = n;
        } else if (mode == 2) {
            n = rnd.next(2, 1000);
            k = rnd.next(1, min(n, 5));
        } else if (mode == 3) {
            n = rnd.next(2, 1000);
            k = rnd.next(max(1, n - 5), n);
        } else if (mode == 4) {
            n = rnd.next(900, 1000);
            k = rnd.next(1, n);
        } else {
            n = rnd.next(1, 1000);
            k = rnd.next(1, n);
        }

        cases.push_back({n, k});
    }

    println(t);
    for (const auto& tc : cases) {
        println(tc.first, tc.second);
    }

    return 0;
}
