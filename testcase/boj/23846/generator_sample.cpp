#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 6);
        k = rnd.next(1, min(8, 456));
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        k = rnd.next(1, min(20, 456));
    } else if (mode == 2) {
        n = rnd.next(50, 200);
        k = rnd.next(1, 456);
    } else if (mode == 3) {
        n = rnd.next(1000, 3000);
        k = rnd.next(1, 30);
    } else if (mode == 4) {
        n = rnd.next(1, 30);
        k = rnd.next(300, 456);
    } else if (mode == 5) {
        n = rnd.any(vector<int>{1, 2, 3, 2998, 2999, 3000});
        k = rnd.next(1, 456);
    } else {
        n = rnd.next(1, 3000);
        k = rnd.any(vector<int>{1, 2, 3, 454, 455, 456});
    }

    println(n, k);
    return 0;
}
