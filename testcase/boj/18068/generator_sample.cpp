#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 100);
    } else if (mode == 2) {
        n = rnd.next(101, 1000);
    } else if (mode == 3) {
        n = rnd.next(1001, 10000);
    } else if (mode == 4) {
        n = rnd.next(49000, 50000);
    } else if (mode == 5) {
        n = rnd.any(vector<int>{1, 2, 3, 4, 49999, 50000});
    } else {
        n = rnd.next(1, 50000);
    }

    println(n);
    return 0;
}
