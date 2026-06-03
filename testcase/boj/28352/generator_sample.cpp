#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {10, 11, 12, 16, 17};

    int mode = rnd.next(0, 3);
    int n;
    if (mode == 0) {
        n = rnd.any(anchors);
    } else if (mode == 1) {
        n = rnd.next(10, 12);
    } else if (mode == 2) {
        n = rnd.next(15, 17);
    } else {
        n = rnd.next(10, 17);
    }

    println(n);
    return 0;
}
