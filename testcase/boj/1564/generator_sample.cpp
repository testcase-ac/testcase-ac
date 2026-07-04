#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(9, 30);
    } else if (mode == 1) {
        vector<int> anchors = {18, 20, 25, 50, 100, 125, 625, 3125};
        int anchor = rnd.any(anchors);
        n = anchor + rnd.next(-3, 3);
    } else if (mode == 2) {
        int exponent = rnd.next(1, 6);
        int base = rnd.any(vector<int>{2, 5, 10});
        int value = 1;
        for (int i = 0; i < exponent; ++i) value *= base;
        n = value + rnd.next(-10, 10);
    } else if (mode == 3) {
        int block = rnd.next(1, 20000);
        n = block * 5 + rnd.next(-2, 2);
    } else if (mode == 4) {
        n = rnd.next(1000, 100000);
    } else {
        n = 1000000 - rnd.next(0, 10000);
    }

    n = max(9, min(1000000, n));
    println(n);
    return 0;
}
