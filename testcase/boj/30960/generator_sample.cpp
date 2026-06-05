#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = 2 * rnd.next(1, 13) + 1;
    vector<int> a;

    if (mode == 0) {
        int start = rnd.next(1, 200);
        int gap = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) a.push_back(start + i * gap);
    } else if (mode == 1) {
        int current = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) {
            current += (i % 3 == 2 ? rnd.next(20, 80) : rnd.next(1, 4));
            a.push_back(current);
        }
    } else if (mode == 2) {
        int left = rnd.next(1, 5000);
        int right = rnd.next(999990000, 1000000000 - n);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                a.push_back(left++);
            } else {
                a.push_back(right++);
            }
        }
    } else if (mode == 3) {
        int base = rnd.next(1, 1000000000 - 10000);
        auto offsets = rnd.distinct(n, 0, 10000);
        for (int x : offsets) a.push_back(base + x);
    } else {
        n = rnd.any(vector<int>{3, 5, 7, 499});
        auto values = rnd.distinct(n, 1, 1000000000);
        for (int x : values) a.push_back(x);
    }

    if (rnd.next(0, 1) == 0) {
        shuffle(a.begin(), a.end());
    } else if (rnd.next(0, 1) == 0) {
        reverse(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
