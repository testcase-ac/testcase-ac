#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;
    long long remainingProduct = 1000000;
    int mode = rnd.next(0, 4);

    auto addCase = [&](int n, int m) {
        if (n > 500000 || m > 500000) return;
        long long product = 1LL * n * m;
        if (product > remainingProduct) return;
        cases.push_back({n, m});
        remainingProduct -= product;
    };

    if (mode == 0) {
        int t = rnd.next(3, 25);
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(2, 15);
            int m = rnd.next(2, 15);
            addCase(n, m);
        }
    } else if (mode == 1) {
        int t = rnd.next(2, 8);
        for (int i = 0; i < t; ++i) {
            int skinnySide = rnd.next(2, 5);
            int maxLongSide = min(500000, static_cast<int>(remainingProduct / skinnySide));
            if (maxLongSide < 2) break;
            int longSide = rnd.next(max(2, maxLongSide / 2), maxLongSide);
            if (rnd.next(0, 1)) {
                addCase(skinnySide, longSide);
            } else {
                addCase(longSide, skinnySide);
            }
        }
    } else if (mode == 2) {
        int t = rnd.next(2, 12);
        for (int i = 0; i < t; ++i) {
            int limit = min(1000, static_cast<int>(remainingProduct / 2));
            if (limit < 2) break;
            int n = rnd.next(2, limit);
            int maxM = min(1000, static_cast<int>(remainingProduct / n));
            if (maxM < 2) break;
            int m = rnd.next(2, maxM);
            addCase(n, m);
        }
    } else {
        int t = rnd.next(10, 80);
        for (int i = 0; i < t; ++i) {
            int n = rnd.next(2, 60);
            int maxM = min(60, static_cast<int>(remainingProduct / n));
            if (maxM < 2) break;
            int m = rnd.next(2, maxM);
            addCase(n, m);
        }
    }

    if (cases.empty()) addCase(2, 2);
    shuffle(cases.begin(), cases.end());

    println(static_cast<int>(cases.size()));
    for (const auto& [n, m] : cases) {
        println(n, m);
    }

    return 0;
}
