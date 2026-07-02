#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> boundaryValues = {1, 2, 7, 8, 19, 20, 21, 349, 350};
    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.any(boundaryValues);
    } else if (mode == 1) {
        n = rnd.next(1, 7);
    } else if (mode == 2) {
        n = rnd.next(8, 20);
    } else if (mode == 3) {
        n = rnd.next(21, 80);
    } else {
        n = rnd.next(81, 350);
    }

    println(n);
    return 0;
}
