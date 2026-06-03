#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int x;
    int y;
    int z;

    if (mode == 0) {
        x = rnd.next(1, 8);
        y = rnd.next(1, 8);
        z = rnd.next(1, 8);
    } else if (mode == 1) {
        x = rnd.next(1, 50);
        y = rnd.next(1, 100 - x);
        z = x + y;
    } else if (mode == 2) {
        x = rnd.next(1, 49);
        y = rnd.next(1, 99 - x);
        z = x + y + rnd.next(1, 100 - x - y);
    } else if (mode == 3) {
        x = rnd.next(2, 100);
        y = rnd.next(1, min(100, x + rnd.next(-1, 1)));
        int sum = x + y;
        z = max(1, min(100, sum - rnd.next(1, min(5, sum - 1))));
    } else if (mode == 4) {
        vector<int> edge = {1, 2, 50, 99, 100};
        x = rnd.any(edge);
        y = rnd.any(edge);
        z = rnd.any(edge);
    } else {
        x = rnd.next(1, 100);
        y = rnd.next(1, 100);
        z = rnd.next(1, 100);
    }

    println(x);
    println(y);
    println(z);
    return 0;
}
