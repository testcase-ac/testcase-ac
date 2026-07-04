#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> smallValues = {1, 2, 3, 4, 5};
    int mode = rnd.next(0, 3);
    int n;

    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 15;
    } else if (mode == 2) {
        n = rnd.any(smallValues);
    } else {
        n = rnd.next(1, 15);
    }

    println(n);
    return 0;
}
