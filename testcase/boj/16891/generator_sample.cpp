#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> anchors = {1, 2, 3, 7, 10, 31, 100, 113, 250, 499, 500};
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.any(anchors);
    } else if (mode == 1) {
        n = rnd.next(1, 20);
    } else if (mode == 2) {
        n = rnd.next(480, 500);
    } else if (mode == 3) {
        n = rnd.next(1, 22);
        n *= n;
        if (n > 500) n = 500;
    } else if (mode == 4) {
        n = rnd.next(1, 500);
    } else {
        n = rnd.wnext(500, rnd.next(-3, 3)) + 1;
    }

    println(n);
    return 0;
}
