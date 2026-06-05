#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int minN = 3;
    const int maxN = 1000000000;
    vector<int> lcms = {2, 6, 12, 60, 60, 420, 840, 2520, 2520, 27720,
                        27720, 360360, 360360, 360360, 720720};

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(minN, maxN);
    } else if (mode == 1) {
        if (rnd.next(2) == 0) {
            n = rnd.next(minN, minN + 200);
        } else {
            n = rnd.next(maxN - 200, maxN);
        }
    } else if (mode == 2) {
        int exponent = rnd.next(2, 29);
        n = 1 << exponent;
        if (rnd.next(3) == 0) {
            n -= rnd.next(0, min(100, n - minN));
        }
    } else if (mode == 3) {
        int base = rnd.any(lcms);
        int multiplier = rnd.next(1, maxN / base);
        n = base * multiplier;
    } else if (mode == 4) {
        vector<int> anchors = {3, 4, 5, 6, 12, 30, 210, 2310, 30030,
                               510510, 9699690, 1000000000};
        n = rnd.any(anchors);
        int delta = rnd.next(-20, 20);
        n = max(minN, min(maxN, n + delta));
    } else {
        int a = rnd.next(2, 31623);
        int b = rnd.next(2, 31623);
        long long value = 1LL * a * b;
        n = static_cast<int>(min<long long>(maxN, max<long long>(minN, value)));
    }

    println(n);
    return 0;
}
