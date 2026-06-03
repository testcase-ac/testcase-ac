#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        vector<int> boundary = {0, 1, 4, 5, 24, 25, 124, 125, 499, 500};
        n = rnd.any(boundary);
    } else if (mode == 1) {
        n = rnd.next(0, 30);
    } else if (mode == 2) {
        n = rnd.next(31, 120);
    } else if (mode == 3) {
        n = rnd.next(121, 300);
    } else if (mode == 4) {
        n = rnd.next(301, 500);
    } else {
        int base = rnd.next(0, 100) * 5;
        int delta = rnd.next(0, 4);
        n = min(500, base + delta);
    }

    println(n);
    return 0;
}
