#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> r(3);
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int x = rnd.next(1, 1000);
        r = {x, x, x};
    } else if (mode == 1) {
        int x = rnd.next(1, 1000);
        int y = rnd.next(1, 1000);
        r = {x, x, y};
        shuffle(r.begin(), r.end());
    } else if (mode == 2) {
        int low = rnd.next(1, 5);
        int high = rnd.next(950, 1000);
        int mid = rnd.next(1, 1000);
        r = {low, mid, high};
        shuffle(r.begin(), r.end());
    } else if (mode == 3) {
        int upper = rnd.next(2, 30);
        for (int i = 0; i < 3; ++i) r[i] = rnd.next(1, upper);
    } else if (mode == 4) {
        int center = rnd.next(1, 1000);
        int spread = rnd.next(0, min(80, max(center - 1, 1000 - center)));
        for (int i = 0; i < 3; ++i) {
            int delta = rnd.next(-spread, spread);
            r[i] = min(1000, max(1, center + delta));
        }
    } else {
        for (int i = 0; i < 3; ++i) r[i] = rnd.next(1, 1000);
    }

    println(r);
    return 0;
}
