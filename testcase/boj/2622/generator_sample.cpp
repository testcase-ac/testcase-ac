#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        vector<int> impossible = {1, 2, 4};
        n = rnd.any(impossible);
    } else if (mode == 1) {
        n = rnd.next(3, 30);
    } else if (mode == 2) {
        int base = rnd.next(1, 80);
        n = 2 * base + 1;
    } else if (mode == 3) {
        int base = rnd.next(2, 80);
        n = 2 * base;
    } else if (mode == 4) {
        vector<int> anchors = {3, 5, 6, 7, 8, 9, 10, 12, 50, 100};
        n = rnd.any(anchors);
    } else {
        n = rnd.next(49900, 50000);
    }

    println(n);
    return 0;
}
