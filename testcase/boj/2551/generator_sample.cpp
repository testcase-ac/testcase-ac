#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static void addRepeated(vector<int>& a, int value, int count) {
    for (int i = 0; i < count; ++i) a.push_back(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    vector<int> a;

    if (mode == 0) {
        int n = rnd.next(1, 3);
        addRepeated(a, rnd.next(1, 10000), n);
    } else if (mode == 1) {
        int n = rnd.next(2, 30);
        addRepeated(a, rnd.any(vector<int>{1, rnd.next(2, 9999), 10000}), n);
    } else if (mode == 2) {
        int left = rnd.next(1, 4999);
        int right = rnd.next(left + 1, 10000);
        int n = rnd.next(2, 36);
        int leftCount = rnd.next(1, n - 1);
        addRepeated(a, left, leftCount);
        addRepeated(a, right, n - leftCount);
    } else if (mode == 3) {
        int n = rnd.next(4, 40);
        int center = rnd.next(2, 9999);
        int radius = rnd.next(1, min(20, min(center - 1, 10000 - center)));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(center - radius, center + radius));
    } else if (mode == 4) {
        int n = rnd.next(5, 41);
        int step = rnd.next(1, 200);
        int maxStart = max(1, 10000 - step * (n - 1));
        int start = rnd.next(1, maxStart);
        for (int i = 0; i < n; ++i) a.push_back(start + step * i);
    } else if (mode == 5) {
        int n = rnd.next(2, 40);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                a.push_back(rnd.next(1, 5));
            } else {
                a.push_back(rnd.next(9996, 10000));
            }
        }
    } else {
        int n = rnd.next(2, 40);
        int lo = rnd.next(1, 9000);
        int hi = rnd.next(lo, min(10000, lo + rnd.next(0, 1000)));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    }

    shuffle(a.begin(), a.end());
    println((int)a.size());
    println(a);

    return 0;
}
