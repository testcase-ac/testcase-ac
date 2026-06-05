#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXV = 10000000;
    int mode = rnd.next(0, 5);
    int s;
    int t;

    if (mode == 0) {
        vector<int> anchors = {1, 2, 3, 8, 16, 17, 9999991, MAXV};
        s = rnd.any(anchors);
        t = s;
    } else if (mode == 1) {
        s = rnd.next(1, 200);
        t = min(MAXV, s + rnd.next(0, 30));
    } else if (mode == 2) {
        int k = rnd.next(2, 3162);
        int center = rnd.next(0, 1) ? k * k : 2 * k * k;
        s = max(1, min(MAXV, center + rnd.next(-5, 5)));
        t = min(MAXV, s + rnd.next(0, 20));
    } else if (mode == 3) {
        s = 1;
        t = rnd.next(1, 1000);
    } else if (mode == 4) {
        t = rnd.next(MAXV - 1000, MAXV);
        s = rnd.next(max(1, t - 100), t);
    } else {
        s = rnd.next(1, MAXV);
        int maxLen = rnd.next(0, 500);
        t = min(MAXV, s + maxLen);
    }

    println(s, t);
    return 0;
}
