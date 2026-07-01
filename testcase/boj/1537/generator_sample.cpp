#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> patternedX = {
        1, 2, 9, 10, 13, 47, 99, 100, 101, 109, 374, 909, 999,
        1000, 1001, 1234, 4321, 4999, 5000, 5001, 9999, 12034,
        54321, 99999, 100000, 654321, 999999, 1000000
    };
    vector<int> smallG = {
        1, 2, 3, 4, 5, 9, 10, 12, 13, 47, 99, 131, 465, 469,
        659, 1024, 1234, 4095, 4999, 5000
    };
    vector<int> largeG = {
        5001, 1234567, 100000000, 999999999, 1999999999, 2000000000
    };

    int mode = rnd.next(0, 7);
    int x = 1;
    int g = 1;

    if (mode == 0) {
        x = rnd.any(patternedX);
        g = x;
    } else if (mode == 1) {
        x = rnd.any(patternedX);
        g = rnd.any(smallG);
    } else if (mode == 2) {
        x = rnd.next(1, 1000000);
        g = rnd.next(1, 5000);
    } else if (mode == 3) {
        x = rnd.any(patternedX);
        g = rnd.any(largeG);
    } else if (mode == 4) {
        x = rnd.next(1, 1000000);
        g = rnd.next(5001, 2000000000);
    } else if (mode == 5) {
        x = rnd.next(999900, 1000000);
        g = rnd.next(1, 2000000000);
    } else if (mode == 6) {
        x = rnd.any(vector<int>{1, 10, 100, 1000, 10000, 100000, 1000000});
        g = rnd.next(1, 2000000000);
    } else {
        x = rnd.next(1, 9999);
        g = rnd.any(vector<int>{1, 12, 131, 465, 469, 659, 1024, 5000, 5001});
    }

    println(x, g);
    return 0;
}
