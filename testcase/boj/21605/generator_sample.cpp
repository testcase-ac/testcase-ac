#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 4);
    } else if (mode == 1) {
        n = rnd.next(5, 10);
    } else if (mode == 2) {
        n = rnd.next(11, 100);
    } else if (mode == 3) {
        n = rnd.next(99990, 100000);
    } else {
        vector<int> interesting = {1, 2, 3, 4, 10, 11, 99999, 100000};
        n = rnd.any(interesting);
    }

    println(n);
    return 0;
}
