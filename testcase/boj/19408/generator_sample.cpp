#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 16);
    } else if (mode == 3) {
        vector<int> nearSamples = {12, 13, 14};
        n = rnd.any(nearSamples);
    } else if (mode == 4) {
        n = rnd.next(90, 100);
    } else {
        n = rnd.next(1, 100);
    }

    println(n);
    return 0;
}
