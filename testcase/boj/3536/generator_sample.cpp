#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.any(vector<int>{1, 2, 3, 4, 5});
    } else if (mode == 1) {
        n = rnd.next(6, 20);
    } else if (mode == 2) {
        n = 2 * rnd.next(1, 50);
    } else if (mode == 3) {
        n = 2 * rnd.next(0, 49) + 1;
    } else if (mode == 4) {
        n = rnd.next(80, 100);
    } else {
        n = rnd.next(1, 100);
    }

    println(n);
    return 0;
}
