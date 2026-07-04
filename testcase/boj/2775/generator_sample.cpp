#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;
    int mode = rnd.next(0, 4);

    auto addCase = [&](int k, int n) {
        cases.push_back({k, n});
    };

    if (mode == 0) {
        int t = rnd.next(2, 8);
        for (int i = 0; i < t; ++i) {
            addCase(rnd.next(1, 14), rnd.next(1, 14));
        }
    } else if (mode == 1) {
        int t = rnd.next(4, 10);
        for (int i = 0; i < t; ++i) {
            int k = rnd.any(vector<int>{1, 2, 13, 14});
            int n = rnd.next(1, 14);
            if (rnd.next(2)) swap(k, n);
            addCase(k, n);
        }
    } else if (mode == 2) {
        int t = rnd.next(4, 12);
        int k = rnd.next(1, 14);
        for (int i = 0; i < t; ++i) {
            addCase(k, rnd.next(1, 14));
        }
    } else if (mode == 3) {
        int t = rnd.next(4, 12);
        int n = rnd.next(1, 14);
        for (int i = 0; i < t; ++i) {
            addCase(rnd.next(1, 14), n);
        }
    } else {
        for (int k : {1, 2, 7, 13, 14}) {
            addCase(k, rnd.next(1, 14));
        }
        for (int n : {1, 2, 7, 13, 14}) {
            addCase(rnd.next(1, 14), n);
        }
        addCase(14, 14);
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [k, n] : cases) {
        println(k);
        println(n);
    }

    return 0;
}
