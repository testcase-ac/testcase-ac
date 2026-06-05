#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int wrapDegree(int value) {
    value %= 360;
    if (value < 0) value += 360;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n1 = rnd.next(0, 359);
    int n2 = rnd.next(0, 359);
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        n2 = n1;
    } else if (mode == 1) {
        n2 = wrapDegree(n1 + 180);
    } else if (mode == 2) {
        int delta = rnd.next(1, 20);
        n2 = wrapDegree(n1 + delta);
    } else if (mode == 3) {
        int delta = rnd.next(1, 20);
        n2 = wrapDegree(n1 - delta);
    } else if (mode == 4) {
        int delta = rnd.next(160, 179);
        n2 = wrapDegree(n1 + delta);
    } else if (mode == 5) {
        int delta = rnd.next(160, 179);
        n2 = wrapDegree(n1 - delta);
    } else if (mode == 6) {
        vector<int> edgeDegrees = {0, 1, 2, 178, 179, 180, 181, 358, 359};
        n1 = rnd.any(edgeDegrees);
        n2 = rnd.any(edgeDegrees);
    } else {
        n1 = rnd.next(0, 359);
        n2 = rnd.next(0, 359);
    }

    println(n1);
    println(n2);

    return 0;
}
