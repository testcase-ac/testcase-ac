#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 5000000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        vector<int> anchors = {2, 3, 4, 5, 6, 29, 30, 31, 32, 97, 98, 99, 100, 101};
        n = rnd.any(anchors);
    } else if (mode == 2) {
        n = rnd.next(13, 1000);
    } else if (mode == 3) {
        n = rnd.next(1001, 200000);
    } else if (mode == 4) {
        n = rnd.next(200001, maxN);
    } else {
        n = maxN - rnd.next(0, 1000);
    }

    println(n);
    return 0;
}
