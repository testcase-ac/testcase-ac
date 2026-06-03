#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int x0 = 0;
    int N = 0;

    if (mode == 0) {
        x0 = rnd.next(0, 1000);
        N = 0;
    } else if (mode == 1) {
        x0 = rnd.any(vector<int>{0, 1, 2, 6, 7, 999, 1000});
        N = rnd.any(vector<int>{0, 1, 2, 999, 1000});
    } else if (mode == 2) {
        x0 = rnd.next(0, 500) * 2;
        N = rnd.next(1, 1000);
    } else if (mode == 3) {
        x0 = rnd.next(0, 499) * 2 + 1;
        N = rnd.next(1, 1000);
    } else if (mode == 4) {
        vector<int> powers;
        for (int x = 1; x <= 1000; x *= 2) {
            powers.push_back(x);
        }
        x0 = rnd.any(powers);
        N = rnd.next(1, 1000);
    } else if (mode == 5) {
        x0 = rnd.next(0, 20);
        N = rnd.next(0, 20);
    } else if (mode == 6) {
        x0 = rnd.next(980, 1000);
        N = rnd.next(980, 1000);
    } else {
        x0 = rnd.next(0, 1000);
        N = rnd.next(0, 1000);
    }

    println(x0, N);
    return 0;
}
