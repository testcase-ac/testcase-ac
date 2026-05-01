#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> special = {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 15, 20, 21,
        22, 23, 30, 31, 32,
        33, 34, 35, 36, 37,
        38, 39, 40, 41, 42,
        43, 44, 45, 46, 47,
        48, 49, 50, 99, 100,
        101, 102, 201, 202, 999,
        1000, 9999, 10000, 99999, 100000
    };

    int type = rnd.next(1, 5);
    int D;

    if (type == 1) {
        // Pick from curated interesting values
        D = rnd.any(special);
    } else if (type == 2) {
        // Very small range
        D = rnd.next(1, 50);
    } else if (type == 3) {
        // Small/medium range
        D = rnd.next(51, 1000);
    } else if (type == 4) {
        // Larger range
        D = rnd.next(1001, 100000);
    } else {
        // Force maximum
        D = 100000;
    }

    println(D);
    return 0;
}
