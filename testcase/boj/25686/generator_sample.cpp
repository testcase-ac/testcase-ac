#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> interesting = {
        2, 3, 4, 5, 8, 9, 10, 15, 16, 17,
        31, 32, 33, 63, 64, 65, 99999, 100000
    };

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 9);
    } else if (mode == 1) {
        n = rnd.next(10, 100);
    } else if (mode == 2) {
        n = rnd.next(101, 1000);
    } else if (mode == 3) {
        n = rnd.next(1001, 100000);
    } else {
        n = rnd.any(interesting);
    }

    println(n);
    return 0;
}
