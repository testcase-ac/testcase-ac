#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.any(vector<int>{0, 1, 4, 20, 42, 47, 52});
    } else if (mode == 1) {
        n = rnd.next(0, 10);
    } else if (mode == 2) {
        n = rnd.next(42, 52);
    } else if (mode == 3) {
        int remainingHands = rnd.next(0, 8);
        int offset = rnd.next(0, 4);
        n = 52 - (remainingHands * 5 + offset);
        if (n < 0) n = 0;
    } else {
        n = rnd.next(0, 52);
    }

    println(n);
    return 0;
}
