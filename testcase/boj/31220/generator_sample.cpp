#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> anchorCases = {
        {2, 2}, {2, 3}, {3, 2}, {3, 3}, {4, 4},
        {2, 17}, {17, 2}, {999, 1000}, {1000, 999}, {1000, 1000}
    };

    int mode = rnd.next(0, 5);
    int n, m;
    if (mode == 0) {
        tie(n, m) = rnd.any(anchorCases);
    } else if (mode == 1) {
        n = rnd.next(2, 6);
        m = rnd.next(2, 6);
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
    } else if (mode == 3) {
        n = rnd.any(vector<int>{2, 3, 4, 5});
        m = rnd.next(20, 80);
        if (rnd.next(0, 1)) swap(n, m);
    } else if (mode == 4) {
        n = rnd.next(950, 1000);
        m = rnd.next(2, 20);
        if (rnd.next(0, 1)) swap(n, m);
    } else {
        n = rnd.next(2, 1000);
        m = rnd.next(2, 1000);
    }

    println(n, m);
    return 0;
}
