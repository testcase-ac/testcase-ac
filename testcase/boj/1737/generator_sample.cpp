#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        vector<int> pivots = {4, 5, 6, 7, 8, 9, 10, 11, 12};
        n = rnd.any(pivots);
    } else if (mode == 2) {
        n = rnd.next(13, 60);
    } else if (mode == 3) {
        n = rnd.next(61, 250);
    } else if (mode == 4) {
        n = rnd.next(251, 750);
    } else {
        n = rnd.next(751, 1000);
    }

    println(n);
    return 0;
}
