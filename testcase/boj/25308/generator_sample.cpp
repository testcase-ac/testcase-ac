#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a(8);
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        fill(a.begin(), a.end(), rnd.next(1, 10000));
    } else if (mode == 1) {
        int lo = rnd.next(1, 9995);
        int hi = rnd.next(lo, min(10000, lo + rnd.next(0, 5)));
        for (int& x : a) x = rnd.next(lo, hi);
    } else if (mode == 2) {
        vector<int> choices;
        int distinct = rnd.next(2, 4);
        for (int i = 0; i < distinct; ++i) choices.push_back(rnd.next(1, 10000));
        for (int& x : a) x = rnd.any(choices);
    } else if (mode == 3) {
        int low = rnd.next(1, 20);
        int high = rnd.next(9980, 10000);
        for (int i = 0; i < 8; ++i) a[i] = (i % 2 == 0 ? low : high);
    } else if (mode == 4) {
        int start = rnd.next(1, 5000);
        int step = rnd.next(1, max(1, (10000 - start) / 7));
        for (int i = 0; i < 8; ++i) a[i] = min(10000, start + i * step + rnd.next(0, step));
    } else if (mode == 5) {
        int center = rnd.next(100, 9900);
        for (int& x : a) x = max(1, min(10000, center + rnd.next(-100, 100)));
    } else {
        for (int& x : a) x = rnd.next(1, 10000);
    }

    shuffle(a.begin(), a.end());
    println(a);
    return 0;
}
