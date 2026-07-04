#include "testlib.h"

#include <array>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    array<int, 5> sampleValues = {1, 2, 10, 50, 100};
    array<int, 5> lossEdges = {0, 1, 25, 80, 99};
    array<int, 4> prizeEdges = {1, 2, 50, 100};
    array<int, 5> lossSharpEdges = {0, 1, 50, 98, 99};

    int deltaL = 1;
    int deltaW = 1;
    int g = 1;
    int l = 0;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        deltaL = rnd.any(sampleValues);
        deltaW = rnd.any(sampleValues);
        g = rnd.any(sampleValues);
        l = rnd.any(lossEdges);
    } else if (mode == 1) {
        deltaL = rnd.next(1, 5);
        deltaW = rnd.next(1, 5);
        g = rnd.next(1, 10);
        l = rnd.next(0, 10);
    } else if (mode == 2) {
        deltaL = rnd.next(90, 100);
        deltaW = rnd.next(90, 100);
        g = rnd.next(90, 100);
        l = rnd.next(90, 99);
    } else if (mode == 3) {
        deltaL = rnd.next(1, 100);
        deltaW = rnd.next(1, 100);
        g = rnd.any(prizeEdges);
        l = rnd.any(lossSharpEdges);
    } else if (mode == 4) {
        int small = rnd.next(1, 10);
        int large = rnd.next(80, 100);
        if (rnd.next(0, 1) == 0) {
            deltaL = small;
            deltaW = large;
        } else {
            deltaL = large;
            deltaW = small;
        }
        g = rnd.next(1, 100);
        l = rnd.next(0, 99);
    } else {
        deltaL = rnd.next(1, 100);
        deltaW = rnd.next(1, 100);
        g = rnd.next(1, 100);
        l = rnd.next(0, 99);
    }

    println(deltaL, deltaW, g, l);
    return 0;
}
