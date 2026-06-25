#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t;
    if (mode == 0) {
        t = 1;
    } else if (mode <= 3) {
        t = rnd.next(2, 12);
    } else {
        t = rnd.next(20, 80);
    }

    vector<int> n(t);
    vector<int> k(t);
    int remainingK = 200000;

    for (int i = 0; i < t; ++i) {
        int casesLeft = t - i;
        int maxK = remainingK - (casesLeft - 1);

        if (mode == 0) {
            n[i] = rnd.any(vector<int>{0, 1, 2, 3, 1000000000});
            k[i] = rnd.any(vector<int>{1, 2, 3, 199999, 200000});
        } else if (mode == 1) {
            n[i] = rnd.next(0, 12);
            k[i] = rnd.next(1, min(maxK, 12));
        } else if (mode == 2) {
            n[i] = rnd.next(0, 1000000000);
            int cap = min(maxK, 2000);
            k[i] = rnd.next(1, cap);
        } else if (mode == 3) {
            n[i] = rnd.any(vector<int>{0, 1, 998244352, 998244353, 1000000000});
            int cap = min(maxK, 200000);
            k[i] = rnd.next(max(1, cap - 1000), cap);
        } else {
            n[i] = rnd.next(0, 50);
            int cap = min(maxK, 20);
            k[i] = rnd.next(1, cap);
        }

        remainingK -= k[i];
    }

    println(t);
    for (int i = 0; i < t; ++i) {
        println(n[i], k[i]);
    }

    return 0;
}
