#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int h;

    if (mode == 0) {
        vector<int> nearBounds = {0, 1, 2, 3, 58, 59, 60};
        h = rnd.any(nearBounds);
    } else if (mode == 1) {
        h = rnd.next(0, 30) * 2;
    } else if (mode == 2) {
        h = rnd.next(0, 29) * 2 + 1;
    } else if (mode == 3) {
        h = rnd.wnext(61, 2);
    } else {
        h = rnd.next(0, 60);
    }

    println(h);
    return 0;
}
