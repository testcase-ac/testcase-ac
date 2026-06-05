#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 0;
    int m = 2;

    if (mode == 0) {
        n = 0;
        m = rnd.next(2, 1000);
    } else if (mode == 1) {
        n = 25;
        m = rnd.next(2, 60);
    } else if (mode == 2) {
        n = rnd.next(22, 25);
        m = rnd.next(2, 12);
    } else if (mode == 3) {
        n = rnd.next(15, 21);
        m = rnd.next(2, 30);
    } else if (mode == 4) {
        n = rnd.next(1, 8);
        m = rnd.next(2, 80);
    } else if (mode == 5) {
        n = rnd.next(9, 18);
        m = rnd.next(200, 1000);
    } else if (mode == 6) {
        vector<int> interestingN = {0, 1, 17, 24, 25};
        vector<int> interestingM = {2, 3, 4, 6, 999, 1000};
        n = rnd.any(interestingN);
        m = rnd.any(interestingM);
    } else {
        n = rnd.next(0, 25);
        m = rnd.next(2, 1000);
    }

    println(n, m);
    return 0;
}
