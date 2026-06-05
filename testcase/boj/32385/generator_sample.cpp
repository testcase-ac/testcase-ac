#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 10);
    } else if (mode == 1) {
        n = rnd.next(11, 100);
    } else if (mode == 2) {
        n = rnd.next(101, 1000);
    } else if (mode == 3) {
        n = rnd.next(9000, 10000);
    } else {
        vector<int> boundaries = {2, 3, 4, 9999, 10000};
        n = rnd.any(boundaries);
    }

    println(n);
    return 0;
}
