#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 1000000;
    int mode = rnd.next(0, 7);
    int k = rnd.next(1, 6);
    int a, b;

    if (mode == 0) {
        a = b = rnd.next(1, MAX_N);
    } else if (mode == 1) {
        a = rnd.next(1, MAX_N - 20);
        b = a + rnd.next(0, 20);
    } else if (mode == 2) {
        a = rnd.next(1, MAX_N - 1000);
        b = a + rnd.next(50, 1000);
    } else if (mode == 3) {
        a = rnd.next(1, 1000);
        b = rnd.next(max(a, 1000), 100000);
    } else if (mode == 4) {
        a = rnd.next(900000, MAX_N);
        b = rnd.next(a, MAX_N);
    } else if (mode == 5) {
        vector<int> anchors = {1, 9, 10, 99, 100, 999, 1000, 9999, 10000, 99999, 100000, 999999, MAX_N};
        int center = rnd.any(anchors);
        int radius = rnd.next(0, 30);
        a = max(1, center - radius);
        b = min(MAX_N, center + rnd.next(0, 30));
        if (a > b) swap(a, b);
    } else if (mode == 6) {
        a = rnd.next(1, 1000);
        b = rnd.next(500000, MAX_N);
    } else {
        a = rnd.next(1, MAX_N);
        int maxWidth = min(MAX_N - a, rnd.next(0, 10000));
        b = a + rnd.next(0, maxWidth);
    }

    if (rnd.next(0, 3) == 0) {
        vector<int> hardK = {1, 2, 3, 6};
        k = rnd.any(hardK);
    }

    println(a, b, k);
    return 0;
}
