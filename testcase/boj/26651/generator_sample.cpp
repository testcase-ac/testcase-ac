#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_X = 1000000000;
    int mode = rnd.next(0, 5);
    int x = 0;

    if (mode == 0) {
        x = rnd.next(0, 100);
    } else if (mode == 1) {
        int near = rnd.next(0, 1000000);
        x = MAX_X - near;
    } else if (mode == 2) {
        int root = rnd.next(0, 31623);
        long long square = 1LL * root * root;
        int delta = rnd.next(-3, 3);
        x = (int)min<long long>(MAX_X, max<long long>(0, square + delta));
    } else if (mode == 3) {
        int a = rnd.next(0, 31623);
        int b = rnd.next(0, 31623);
        x = (int)min<long long>(MAX_X, 1LL * a * b);
    } else if (mode == 4) {
        vector<int> anchors = {0, 1, 2, 25, 26, 27, 999999937, MAX_X};
        int anchor = rnd.any(anchors);
        int delta = rnd.next(-50, 50);
        x = min(MAX_X, max(0, anchor + delta));
    } else {
        x = rnd.next(0, MAX_X);
    }

    println(x);
    return 0;
}
