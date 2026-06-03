#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int x;

    if (mode == 0) {
        x = rnd.next(1, 30);
    } else if (mode == 1) {
        int residue = rnd.next(0, 2);
        int k = rnd.next(0, 333333333);
        x = k * 3 + residue;
        if (x < 1) x += 3;
        if (x > 1000000000) x -= 3;
    } else if (mode == 2) {
        x = 1000000000 - rnd.next(0, 30);
    } else if (mode == 3) {
        vector<int> edges = {1, 2, 3, 999999998, 999999999, 1000000000};
        x = rnd.any(edges);
    } else {
        x = rnd.next(1, 1000000000);
    }

    println(x);
    return 0;
}
