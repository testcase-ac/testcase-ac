#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

long long luckyNumber(int digits) {
    string s;
    for (int i = 0; i < digits; ++i) {
        s += rnd.next(2) == 0 ? '4' : '7';
    }
    return stoll(s);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000000;
    int mode = rnd.next(0, 5);
    long long n = 1;

    if (mode == 0) {
        n = rnd.next(1, 30);
    } else if (mode == 1) {
        vector<int> anchors = {1, 2, 3, 4, 7, 8, 11, 12, 13, 14, 18, 24, 25, 26};
        n = rnd.any(anchors) + rnd.next(0, 2);
    } else if (mode == 2) {
        int terms = rnd.next(1, 8);
        n = 0;
        for (int i = 0; i < terms; ++i) {
            n += luckyNumber(rnd.next(1, 3));
        }
    } else if (mode == 3) {
        n = luckyNumber(rnd.next(1, 9));
    } else if (mode == 4) {
        n = maxN - rnd.next(0, 500);
    } else {
        n = rnd.next(1, maxN);
    }

    n = max(1LL, min(n, static_cast<long long>(maxN)));
    println(n);
    return 0;
}
