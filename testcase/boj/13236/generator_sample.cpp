#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> boundaries = {1, 2, 3, 99999, 100000};
    vector<int> powersOfTwo;
    for (int x = 1; x <= 100000; x *= 2) {
        powersOfTwo.push_back(x);
    }

    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = rnd.any(boundaries);
    } else if (mode == 1) {
        n = rnd.any(powersOfTwo);
    } else if (mode == 2) {
        n = 2 * rnd.next(1, 50000);
    } else if (mode == 3) {
        n = 2 * rnd.next(0, 49999) + 1;
    } else if (mode == 4) {
        n = rnd.next(1, 1000);
    } else if (mode == 5) {
        n = rnd.next(90000, 100000);
    } else {
        n = rnd.next(1, 100000);
    }

    println(n);
    return 0;
}
