#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int clampN(int n) {
    return max(2, min(1000000, n));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 14);
    vector<int> cases;
    cases.reserve(t);

    while ((int)cases.size() < t) {
        int mode = rnd.next(8);
        int n;

        if (mode == 0) {
            n = rnd.next(2, 40);
        } else if (mode == 1) {
            n = 2 * rnd.next(1, 200000);
            if (n % 3 == 0) n += 2;
        } else if (mode == 2) {
            n = 3 * rnd.next(1, 333333);
        } else if (mode == 3) {
            n = 2 * rnd.next(2, 20);
            for (int i = 1; i < rnd.next(1, 6); ++i) n *= 2;
        } else if (mode == 4) {
            n = 3;
            for (int i = 0; i < rnd.next(1, 10); ++i) n *= 3;
        } else if (mode == 5) {
            n = rnd.next(999900, 1000000);
        } else if (mode == 6) {
            int base = rnd.next(2, 333333) * 3;
            n = base + rnd.any(vector<int>{-1, 1, 2});
        } else {
            n = rnd.next(2, 500000) * 2 + 1;
        }

        cases.push_back(clampN(n));
    }

    shuffle(cases.begin(), cases.end());

    println(t);
    for (int n : cases) {
        printf("\n");
        println(n);
    }

    return 0;
}
