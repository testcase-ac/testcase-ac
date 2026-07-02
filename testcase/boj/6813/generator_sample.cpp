#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> thresholds = {
        7, 8, 10, 11, 14, 15, 20, 21, 25, 26, 29, 30, 31
    };

    int mode = rnd.next(0, 4);
    int w;
    if (mode == 0) {
        w = rnd.any(thresholds);
    } else if (mode == 1) {
        int base = rnd.any(thresholds);
        w = max(7, base + rnd.next(-2, 2));
    } else if (mode == 2) {
        w = rnd.next(7, 60);
    } else if (mode == 3) {
        w = rnd.next(61, 1000);
    } else {
        w = rnd.next(1001, 1000000);
    }

    println(w);
    return 0;
}
