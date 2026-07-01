#include "testlib.h"

#include <cstdio>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {
        0, 1, 2, 999999, 1000000, 1000001, 1999998, 1999999, 2000000
    };

    int millionths;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        millionths = anchors[rnd.next(static_cast<int>(anchors.size()))];
    } else if (mode == 1) {
        int center = anchors[rnd.next(static_cast<int>(anchors.size()))];
        int delta = rnd.next(-25, 25);
        millionths = max(0, min(2000000, center + delta));
    } else if (mode == 2) {
        millionths = rnd.next(0, 1000000);
    } else if (mode == 3) {
        millionths = rnd.next(1000000, 2000000);
    } else {
        millionths = rnd.next(0, 2000000);
    }

    printf("%d.%06d\n", millionths / 1000000, millionths % 1000000);
    return 0;
}
