#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 4);
        k = rnd.next(1, 100);
    } else if (mode == 1) {
        n = rnd.next(5, 20);
        k = rnd.next(1, 12);
    } else if (mode == 2) {
        n = rnd.next(21, 200);
        k = rnd.next(1, 100);
    } else if (mode == 3) {
        vector<int> boundaryN = {1, 2, 3, 4, 5, 999999, 1000000};
        vector<int> boundaryK = {1, 2, 5, 99, 100};
        n = rnd.any(boundaryN);
        k = rnd.any(boundaryK);
    } else if (mode == 4) {
        n = rnd.next(900000, 1000000);
        k = rnd.next(1, 100);
    } else {
        n = rnd.next(1, 1000000);
        k = rnd.next(1, 100);
    }

    println(n, k);
    return 0;
}
