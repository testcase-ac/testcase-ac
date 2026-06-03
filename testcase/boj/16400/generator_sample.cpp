#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;

    if (mode == 0) {
        n = rnd.next(2, 20);
    } else if (mode == 1) {
        n = rnd.next(21, 200);
    } else if (mode == 2) {
        n = rnd.next(201, 2000);
    } else if (mode == 3) {
        n = rnd.next(2001, 10000);
    } else if (mode == 4) {
        n = rnd.next(10001, 40000);
    } else if (mode == 5) {
        vector<int> primeLike = {3, 5, 7, 11, 13, 17, 19, 97, 997, 1009, 9973, 39989};
        n = rnd.any(primeLike);
    } else if (mode == 6) {
        int root = rnd.next(2, 200);
        n = root * root;
    } else {
        n = 40000 - rnd.next(0, 200);
    }

    println(n);
    return 0;
}
