#include "testlib.h"
#include <string>

using namespace std;

static string makeLeftAfterimage(int trailLength) {
    return "@" + string(trailLength, '=');
}

static string makeRightAfterimage(int trailLength) {
    return string(trailLength, '=') + "@";
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int leftCount;
    int rightCount;
    int maxTrail;

    if (mode == 0) {
        leftCount = 1;
        rightCount = 1;
        maxTrail = rnd.next(1, 3);
    } else if (mode == 1) {
        leftCount = rnd.next(1, 3);
        rightCount = rnd.next(6, 12);
        maxTrail = rnd.next(1, 4);
    } else if (mode == 2) {
        leftCount = rnd.next(6, 12);
        rightCount = rnd.next(1, 3);
        maxTrail = rnd.next(1, 4);
    } else if (mode == 3) {
        leftCount = rnd.next(2, 8);
        rightCount = rnd.next(2, 8);
        maxTrail = rnd.next(5, 18);
    } else {
        leftCount = rnd.next(20, 80);
        rightCount = rnd.next(20, 80);
        maxTrail = rnd.next(1, 5);
    }

    string s;
    for (int i = 0; i < leftCount; ++i) {
        s += makeLeftAfterimage(rnd.next(1, maxTrail));
    }

    s += "(^0^)";

    for (int i = 0; i < rightCount; ++i) {
        s += makeRightAfterimage(rnd.next(1, maxTrail));
    }

    println(s);
    return 0;
}
