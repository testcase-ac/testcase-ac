#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int P = rnd.next(8, 20);
    vector<tuple<int, int, int, int>> cases;
    cases.reserve(P);

    auto addCase = [&](int K, int n, int m, int k) {
        cases.emplace_back(K, n, m, k);
    };

    addCase(1, 1, 0, 1);
    addCase(1000000000, 30, 28, 29);
    addCase(rnd.next(0, 1000000000), 30, 0, rnd.next(1, 29));
    addCase(rnd.next(0, 1000000000), rnd.next(20, 30), 1, 2);

    while ((int)cases.size() < P) {
        int mode = rnd.next(0, 5);
        int n;
        int k;
        int m;

        if (mode == 0) {
            n = rnd.next(1, 5);
            k = rnd.next(1, min(29, n + 3));
            m = rnd.next(0, k - 1);
        } else if (mode == 1) {
            n = rnd.next(24, 30);
            k = rnd.next(1, 29);
            m = rnd.next(0, k - 1);
        } else if (mode == 2) {
            k = rnd.next(2, 29);
            m = rnd.next(0, k - 1);
            n = rnd.next(k, 30);
        } else if (mode == 3) {
            k = rnd.any(vector<int>{1, 2, 3, 5, 10, 15, 29});
            m = rnd.next(0, k - 1);
            n = rnd.next(1, 30);
        } else {
            n = rnd.next(1, 30);
            k = rnd.next(1, 29);
            m = rnd.next(0, k - 1);
        }

        int K;
        if (rnd.next(0, 4) == 0) {
            K = rnd.any(vector<int>{0, 1, 999999999, 1000000000});
        } else {
            K = rnd.next(0, 1000000000);
        }
        addCase(K, n, m, k);
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [K, n, m, k] : cases) {
        println(K, n, m, k);
    }

    return 0;
}
