#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int s;

    if (mode == 0) {
        n = rnd.next(1, 8);
        s = rnd.next(1, min(20, 1000));
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        int leaves = n - 1;
        s = leaves * (leaves - 1) / 2;
        s = max(1, min(s, 1000));
    } else if (mode == 2) {
        n = rnd.next(3, 30);
        int internal = rnd.next(1, n - 1);
        int leaves = n - internal;
        s = leaves * (leaves - 1) / 2;
        for (int i = 0; i < internal; ++i) s += rnd.next(0, min(i, 6));
        s = max(1, min(s, 1000));
    } else if (mode == 3) {
        n = rnd.next(20, 50);
        s = rnd.next(900, 1000);
    } else if (mode == 4) {
        n = rnd.next(1, 50);
        s = rnd.next(1, 1000);
    } else {
        vector<int> interestingN = {1, 2, 3, 4, 5, 10, 25, 50};
        vector<int> interestingS = {1, 2, 3, 4, 10, 100, 999, 1000};
        n = rnd.any(interestingN);
        s = rnd.any(interestingS);
    }

    println(n, s);
    return 0;
}
