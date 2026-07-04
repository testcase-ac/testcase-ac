#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> boundaryValues = {1, 2, 3, 4, 5, 6, 9, 997, 998, 999, 1000};
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.any(boundaryValues);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
    } else {
        int remainder = rnd.next(0, 2);
        int minValue = remainder == 0 ? 3 : remainder;
        int maxK = (1000 - minValue) / 3;
        n = minValue + 3 * rnd.next(0, maxK);
    }

    println(n);
    return 0;
}
