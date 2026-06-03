#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> slime;

    if (mode == 0) {
        n = 2;
        slime = {rnd.next(1, 100), rnd.next(1, 100)};
    } else if (mode == 1) {
        n = rnd.next(3, 10);
        int value = rnd.next(1, 100);
        slime.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(3, 15);
        for (int i = 0; i < n; ++i) {
            slime.push_back(i % 2 == 0 ? rnd.next(1, 5) : rnd.next(80, 100));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 25);
        int low = rnd.next(1, 40);
        int high = rnd.next(low, 100);
        for (int i = 0; i < n; ++i) {
            slime.push_back(rnd.next(low, high));
        }
    } else if (mode == 4) {
        n = rnd.next(20, 60);
        for (int i = 0; i < n; ++i) {
            slime.push_back(rnd.wnext(100, 3) + 1);
        }
    } else if (mode == 5) {
        n = rnd.next(40, 100);
        for (int i = 0; i < n; ++i) {
            slime.push_back(rnd.wnext(100, -3) + 1);
        }
    } else {
        n = 100;
        for (int i = 0; i < n; ++i) {
            slime.push_back(rnd.next(1, 100));
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(slime.begin(), slime.end());
    }

    println(n);
    println(slime);

    return 0;
}
