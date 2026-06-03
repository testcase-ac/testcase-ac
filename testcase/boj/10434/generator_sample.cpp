#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> boundary = {1, 2, 3, 4, 7, 10, 100, 9999, 10000};
    const vector<int> happyPrimes = {7, 13, 19, 23, 31, 79, 97, 313, 331, 367, 379, 383};
    const vector<int> unhappyPrimes = {2, 3, 5, 11, 17, 29, 41, 47, 71, 101, 9973};
    const vector<int> composites = {4, 6, 8, 9, 12, 49, 121, 169, 1000, 9999};

    int p = rnd.next(6, 20);
    println(p);

    int smallK = rnd.next(1, 1000);
    for (int i = 0; i < p; ++i) {
        int k;
        if (i == 0 && rnd.next(2) == 0) {
            k = 1000000000;
        } else if (rnd.next(4) == 0) {
            k = rnd.next(100000000, 1000000000);
        } else {
            k = smallK + i;
        }

        int mode = rnd.next(6);
        int m;
        if (mode == 0) {
            m = rnd.any(boundary);
        } else if (mode == 1) {
            m = rnd.any(happyPrimes);
        } else if (mode == 2) {
            m = rnd.any(unhappyPrimes);
        } else if (mode == 3) {
            m = rnd.any(composites);
        } else if (mode == 4) {
            m = rnd.next(1, 150);
        } else {
            m = rnd.next(1, 10000);
        }

        println(k, m);
    }

    return 0;
}
