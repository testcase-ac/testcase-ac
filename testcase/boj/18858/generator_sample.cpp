#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> fixed = {
        {1, 1}, {1, 100}, {2, 1}, {2, 100}, {3, 2}, {1000, 100}
    };

    int mode = rnd.next(0, 7);
    int n, m;

    if (mode == 0) {
        tie(n, m) = rnd.any(fixed);
    } else if (mode == 1) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 5);
    } else if (mode == 2) {
        n = rnd.next(1, 30);
        m = rnd.next(1, 10);
    } else if (mode == 3) {
        n = rnd.next(31, 120);
        m = rnd.next(1, 20);
    } else if (mode == 4) {
        n = rnd.next(1, 80);
        m = rnd.next(80, 100);
    } else if (mode == 5) {
        n = rnd.next(900, 1000);
        m = rnd.next(1, 8);
    } else if (mode == 6) {
        n = rnd.next(900, 1000);
        m = rnd.next(90, 100);
    } else {
        n = rnd.wnext(1000, 3) + 1;
        m = rnd.wnext(100, rnd.next(-2, 2)) + 1;
    }

    println(n, m);
    return 0;
}
