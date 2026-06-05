#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int x;

    if (mode == 0) {
        x = rnd.next(-10, 10);
    } else if (mode == 1) {
        vector<int> nearBounds = {-1000, -999, -998, 998, 999, 1000};
        x = rnd.any(nearBounds);
    } else if (mode == 2) {
        x = rnd.any(vector<int>{-1, 0, 1});
    } else if (mode == 3) {
        int magnitude = rnd.next(1, 1000);
        x = rnd.next(0, 1) == 0 ? -magnitude : magnitude;
    } else {
        x = rnd.next(-1000, 1000);
    }

    println(x);
    return 0;
}
