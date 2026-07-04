#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int d;

    if (mode == 0) {
        n = rnd.next(2, 12);
        d = rnd.next(1, 6);
    } else if (mode == 1) {
        n = 2 * rnd.next(1, 19);
        d = rnd.next(1, n / 2);
    } else if (mode == 2) {
        n = 2 * rnd.next(1, 19);
        d = n / 2;
    } else if (mode == 3) {
        n = 2 * rnd.next(1, 18);
        d = rnd.next(n / 2 + 1, 19);
    } else if (mode == 4) {
        n = 2 * rnd.next(1, 18) + 1;
        d = rnd.next(1, 19);
    } else if (mode == 5) {
        n = rnd.any(vector<int>{2, 3, 4, 36, 37, 38});
        d = rnd.any(vector<int>{1, 2, 18, 19});
    } else {
        n = rnd.next(2, 38);
        d = rnd.next(1, 19);
    }

    println(n, d);
    return 0;
}
