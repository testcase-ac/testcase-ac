#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 500000;
    vector<int> tiny = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 16, 30, 60};
    vector<int> divisorRich = {
        72, 120, 180, 240, 360, 720, 840, 1260, 1680, 2520,
        5040, 7560, 10080, 20160, 27720, 45360, 83160, 110880,
        166320, 221760, 332640, 498960
    };
    vector<int> primeSensitive = {
        11, 17, 29, 41, 59, 83, 101, 197, 997, 1009,
        10007, 10009, 499979, 499981, 499993
    };
    vector<int> powers = {
        32, 64, 81, 128, 243, 256, 512, 729, 1024, 2048,
        4096, 8192, 16384, 32768, 59049, 65536, 131072, 262144
    };
    vector<int> nearLimit = {
        499900, 499950, 499980, 499990, 499996, 499997,
        499998, 499999, 500000
    };

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = rnd.any(tiny);
    } else if (mode == 1) {
        n = rnd.any(divisorRich);
    } else if (mode == 2) {
        n = rnd.any(primeSensitive);
    } else if (mode == 3) {
        n = rnd.any(powers);
    } else if (mode == 4) {
        n = rnd.any(nearLimit);
    } else if (mode == 5) {
        int base = rnd.any(divisorRich);
        n = min(MAX_N, base + rnd.next(-12, 12));
    } else if (mode == 6) {
        n = rnd.next(1, 2000);
    } else {
        n = rnd.next(1, MAX_N);
    }

    println(n);
    return 0;
}
