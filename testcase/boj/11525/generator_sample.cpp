#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int p;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        p = rnd.next(1, 4);
    } else if (mode == 1) {
        p = rnd.next(5, 20);
    } else if (mode == 2) {
        p = rnd.next(30, 80);
    } else {
        p = rnd.next(1, 100);
    }

    vector<int> usefulN = {2, 3, 4, 5, 6, 10, 15, 30, 57, 99, 100,
                           101, 210, 999, 1000, 1001, 5000, 9999, 10000};
    shuffle(usefulN.begin(), usefulN.end());

    println(p);
    for (int i = 0; i < p; ++i) {
        int kMode = rnd.next(0, 3);
        int k;
        if (kMode == 0) {
            k = i + 1;
        } else if (kMode == 1) {
            k = rnd.next(1, 1000);
        } else {
            k = rnd.next(1, 1000000000);
        }

        int nMode = rnd.next(0, 5);
        int n;
        if (nMode == 0) {
            n = rnd.any(usefulN);
        } else if (nMode == 1) {
            n = rnd.next(2, 20);
        } else if (nMode == 2) {
            n = rnd.next(21, 300);
        } else if (nMode == 3) {
            n = rnd.next(301, 3000);
        } else {
            n = rnd.next(9000, 10000);
        }

        println(k, n);
    }

    return 0;
}
