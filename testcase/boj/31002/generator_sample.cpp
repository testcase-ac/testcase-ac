#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int minN = 3;
    const int maxN = 100000;
    const int maxK = 100000;

    int mode = rnd.next(6);
    int n, k;

    if (mode == 0) {
        vector<int> ns = {minN, 4, 5, 10};
        n = rnd.any(ns);
        k = rnd.next(0, 5);
    } else if (mode == 1) {
        n = rnd.next(minN, 20);
        k = rnd.any(vector<int>{0, 1, 2, 3});
    } else if (mode == 2) {
        n = rnd.next(minN, 200);
        k = rnd.next(4, 200);
    } else if (mode == 3) {
        n = rnd.next(maxN - 1000, maxN);
        k = rnd.next(0, 50);
    } else if (mode == 4) {
        n = rnd.next(minN, 1000);
        k = rnd.next(maxK - 1000, maxK);
    } else {
        n = rnd.next(minN, maxN);
        k = rnd.next(0, maxK);
    }

    println(n, k);
    return 0;
}
