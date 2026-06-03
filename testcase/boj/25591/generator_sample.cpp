#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int x, y;

    if (mode == 0) {
        x = rnd.next(90, 99);
        y = rnd.next(90, 99);
    } else if (mode == 1) {
        x = rnd.next(45, 60);
        y = rnd.next(45, 60);
    } else if (mode == 2) {
        x = rnd.next(10, 25);
        y = rnd.next(10, 35);
    } else if (mode == 3) {
        x = rnd.any(vector<int>{10, 11, 19, 20, 48, 49, 50, 90, 97, 98, 99});
        y = rnd.next(10, 99);
    } else if (mode == 4) {
        x = rnd.next(10, 99);
        y = rnd.any(vector<int>{10, 11, 19, 20, 48, 49, 50, 90, 97, 98, 99});
    } else {
        x = rnd.next(10, 99);
        y = rnd.next(10, 99);
    }

    if (rnd.next(0, 1)) swap(x, y);

    println(x, y);
    return 0;
}
