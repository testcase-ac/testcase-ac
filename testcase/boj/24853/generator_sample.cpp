#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> xInteresting = {0, 1, 49, 50, 74, 75, 76, 77, 99, 100};
    vector<int> tInteresting = {1, 2, 3, 6, 12, 24, 25, 60, 123, 99999, 100000};

    int mode = rnd.next(0, 5);
    int x;
    int t;

    if (mode == 0) {
        x = rnd.any(xInteresting);
        t = rnd.any(tInteresting);
    } else if (mode == 1) {
        x = rnd.any(xInteresting);
        t = rnd.next(1, 100000);
    } else if (mode == 2) {
        x = rnd.next(0, 100);
        t = rnd.any(tInteresting);
    } else if (mode == 3) {
        x = rnd.next(0, 100);
        t = 6 * rnd.next(1, 16666);
    } else if (mode == 4) {
        x = rnd.next(0, 100);
        t = rnd.next(1, 200);
    } else {
        x = rnd.next(0, 100);
        t = rnd.next(1, 100000);
    }

    println(x, t);
    return 0;
}
