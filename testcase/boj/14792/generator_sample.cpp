#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;
    auto addCase = [&](int n, int k) {
        n = max(1, min(n, 1000));
        k = max(1, min(k, n));
        cases.push_back({n, k});
    };

    addCase(1, 1);
    addCase(2, rnd.next(1, 2));
    addCase(3, rnd.next(1, 3));
    addCase(4, 2);
    addCase(5, 2);
    addCase(6, 2);

    for (int i = 0; i < 8; ++i) {
        int n = rnd.next(1, 30);
        int mode = rnd.next(0, 4);
        if (mode == 0) addCase(n, 1);
        else if (mode == 1) addCase(n, n);
        else if (mode == 2) addCase(n, (n + 1) / 2);
        else addCase(n, rnd.next(1, n));
    }

    vector<int> pivots = {31, 32, 33, 63, 64, 65, 127, 128, 129, 255, 256, 257};
    shuffle(pivots.begin(), pivots.end());
    int pivotCount = rnd.next(4, 8);
    for (int i = 0; i < pivotCount; ++i) {
        int n = pivots[i];
        int kMode = rnd.next(0, 5);
        if (kMode == 0) addCase(n, 1);
        else if (kMode == 1) addCase(n, n);
        else if (kMode == 2) addCase(n, n / 2);
        else if (kMode == 3) addCase(n, min(n, n / 2 + 1));
        else addCase(n, rnd.next(1, n));
    }

    addCase(999, rnd.next(1, 999));
    addCase(1000, 1);
    addCase(1000, rnd.next(495, 505));
    addCase(1000, 1000);

    int extra = rnd.next(5, 15);
    for (int i = 0; i < extra && (int)cases.size() < 100; ++i) {
        int n;
        if (rnd.next(0, 3) == 0) n = rnd.next(1, 50);
        else if (rnd.next(0, 1) == 0) n = rnd.next(51, 300);
        else n = rnd.next(301, 1000);

        int bias = rnd.next(0, 5);
        int k;
        if (bias == 0) k = 1;
        else if (bias == 1) k = n;
        else if (bias == 2) k = max(1, n / 2 + rnd.next(-2, 2));
        else k = rnd.next(1, n);
        addCase(n, k);
    }

    shuffle(cases.begin(), cases.end());
    println((int)cases.size());
    for (auto [n, k] : cases) println(n, k);

    return 0;
}
