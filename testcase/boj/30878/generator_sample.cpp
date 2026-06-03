#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> landmarks = {1, 2, 3, 4, 5, 6, 10, 12, 15, 20, 30, 45, 59, 60};
    int mode = rnd.next(0, 4);
    int m;

    if (mode == 0) {
        m = rnd.any(landmarks);
    } else if (mode == 1) {
        m = rnd.next(1, 10);
    } else if (mode == 2) {
        m = rnd.next(51, 60);
    } else if (mode == 3) {
        m = rnd.next(1, 20) * 3;
    } else {
        m = rnd.next(1, 60);
    }

    println(m);
    return 0;
}
