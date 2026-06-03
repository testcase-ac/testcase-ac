#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MIN_N = 5;
    const int MAX_N = 200000000;

    vector<int> anchors = {
        MIN_N,
        6,
        7,
        29,
        30,
        31,
        44,
        45,
        46,
        100000000,
        MAX_N - 1,
        MAX_N
    };

    int mode = rnd.next(6);
    int n;

    if (mode == 0) {
        n = rnd.next(MIN_N, 20);
    } else if (mode == 1) {
        n = rnd.any(anchors);
    } else if (mode == 2) {
        n = rnd.next(21, 1000);
    } else if (mode == 3) {
        n = rnd.next(1001, 1000000);
    } else if (mode == 4) {
        n = rnd.next(MAX_N - 1000, MAX_N);
    } else {
        n = rnd.next(MIN_N, MAX_N);
    }

    println(n);
    return 0;
}
