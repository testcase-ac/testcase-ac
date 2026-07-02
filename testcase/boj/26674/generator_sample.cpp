#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 80 : 30);
    int targetM = rnd.next(1, mode == 5 ? 120 : 45);
    vector<tuple<int, int, int>> ops;

    auto addOp = [&](int l, int r, int k) {
        if (l > r) swap(l, r);
        l = max(l, 1);
        r = min(r, n);
        ops.emplace_back(l, r, k);
    };

    if (mode == 0) {
        for (int i = 0; i < targetM; ++i) {
            int l = rnd.next(1, n);
            int r = rnd.next(l, n);
            int k = rnd.next(1, 3);
            addOp(l, r, k);
        }
    } else if (mode == 1) {
        for (int i = 0; i < targetM; ++i) {
            int p = rnd.next(1, n);
            int k = rnd.next(1, 3);
            addOp(p, p, k);
        }
    } else if (mode == 2) {
        int a = rnd.next(1, n);
        int b = rnd.next(a, n);
        addOp(a, b, 1);
        addOp(rnd.next(1, a), rnd.next(b, n), 2);
        for (int i = 2; i < targetM; ++i) {
            int l = rnd.next(1, n);
            int width = rnd.next(0, min(n - l, 8));
            int k = rnd.next(1, 2);
            addOp(l, l + width, k);
        }
    } else if (mode == 3) {
        for (int i = 0; i < targetM; ++i) {
            int l = rnd.next(1, n);
            int r = rnd.next(l, n);
            int k = (i % 4 == 0) ? 3 : rnd.next(1, 2);
            addOp(l, r, k);
        }
    } else if (mode == 4) {
        for (int i = 0; i < targetM; ++i) {
            int k = rnd.next(1, 3);
            if (rnd.next(0, 1) == 0) {
                addOp(1, rnd.next(1, n), k);
            } else {
                addOp(rnd.next(1, n), n, k);
            }
        }
    } else {
        int block = max(1, n / rnd.next(2, 6));
        for (int start = 1; start <= n && (int)ops.size() < targetM; start += block) {
            int end = min(n, start + block - 1);
            addOp(start, end, rnd.next(1, 3));
            if ((int)ops.size() < targetM) addOp(start, end, rnd.next(1, 3));
        }
        while ((int)ops.size() < targetM) {
            int l = rnd.next(1, n);
            int r = rnd.next(l, min(n, l + block));
            addOp(l, r, rnd.next(1, 3));
        }
    }

    shuffle(ops.begin(), ops.end());
    println(n, (int)ops.size());
    for (auto [l, r, k] : ops) {
        println(l, r, k);
    }

    return 0;
}
