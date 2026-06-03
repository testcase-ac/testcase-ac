#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int kMaxN = 1000000000;
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(0, 9);
    } else if (mode == 1) {
        n = rnd.next(0, 1000);
    } else if (mode == 2) {
        int residue = rnd.next(0, 9);
        int block = rnd.next(0, 100000000);
        n = block * 10 + residue;
    } else if (mode == 3) {
        vector<int> anchors = {9, 10, 11, 999, 1000, 1001, kMaxN - 10, kMaxN - 1, kMaxN};
        n = rnd.any(anchors);
    } else {
        n = rnd.next(0, kMaxN);
    }

    println(n);
    return 0;
}
