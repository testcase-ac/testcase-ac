#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        vector<int> edge = {0, 1, 2, 999, 1000};
        n = rnd.any(edge);
    } else if (mode == 1) {
        n = rnd.next(0, 20);
    } else if (mode == 2) {
        vector<int> nearSamples = {4, 5, 6, 7, 8, 9, 99, 100, 101};
        n = rnd.any(nearSamples);
    } else if (mode == 3) {
        int base = 1 << rnd.next(0, 9);
        int delta = rnd.next(-2, 2);
        n = max(0, min(1000, base + delta));
    } else if (mode == 4) {
        n = rnd.next(21, 300);
    } else {
        n = rnd.next(700, 1000);
    }

    println(n);
    return 0;
}
