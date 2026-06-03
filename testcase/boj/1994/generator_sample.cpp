#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 25);
        int value = rnd.next(0, 999999999);
        a.assign(n, value);
    } else if (mode == 1) {
        int n = rnd.next(2, 35);
        int diff = rnd.next(1, 1000);
        int start = rnd.next(0, 999999999 - diff * (n - 1));
        for (int i = 0; i < n; ++i) a.push_back(start + diff * i);
    } else if (mode == 2) {
        int apLen = rnd.next(3, 20);
        int noise = rnd.next(0, 15);
        int diff = rnd.next(1, 100000);
        int start = rnd.next(0, 999999999 - diff * (apLen - 1));
        for (int i = 0; i < apLen; ++i) a.push_back(start + diff * i);
        for (int i = 0; i < noise; ++i) a.push_back(rnd.next(0, 999999999));
    } else if (mode == 3) {
        int n = rnd.next(5, 40);
        int center = rnd.next(0, 999999999);
        int span = rnd.next(0, 30);
        for (int i = 0; i < n; ++i) {
            int lo = max(0, center - span);
            int hi = min(999999999, center + span);
            a.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 4) {
        int n = rnd.next(4, 30);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) a.push_back(rnd.next(0, 2000));
            else a.push_back(rnd.next(999997999, 999999999));
        }
    } else {
        int n = rnd.next(1, 45);
        int maxValue = rnd.next(0, 200);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, maxValue));
    }

    shuffle(a.begin(), a.end());

    println((int)a.size());
    for (int x : a) println(x);

    return 0;
}
