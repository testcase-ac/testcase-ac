#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int nearPowerOfTwo() {
    int bit = rnd.next(0, 29);
    int base = 1 << bit;
    int delta = rnd.next(-3, 3);
    return max(1, min(1000000000, base + delta));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> nValues = {1, 2, 3, 4, 5, 7, 8, 15, 16, 31, 32, 1000000000};

    int extra = rnd.next(6, 18);
    for (int i = 0; i < extra; ++i) {
        int mode = rnd.next(0, 4);
        if (mode == 0) {
            nValues.push_back(rnd.next(1, 20));
        } else if (mode == 1) {
            nValues.push_back(nearPowerOfTwo());
        } else if (mode == 2) {
            int center = rnd.next(900000000, 1000000000);
            nValues.push_back(center);
        } else {
            nValues.push_back(rnd.next(1, 1000000000));
        }
    }

    shuffle(nValues.begin(), nValues.end());
    println(static_cast<int>(nValues.size()));
    for (int n : nValues) {
        println(n);
    }

    return 0;
}
