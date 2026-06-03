#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edge = {1, 2, 3, 4, 5, 10, 999, 1000};
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 997};
    vector<int> powers = {4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 216, 243, 512, 625, 729, 1000};
    vector<int> composites = {6, 12, 18, 24, 36, 48, 60, 72, 84, 90, 120, 180, 210, 360, 420, 504, 720, 840};

    int t = rnd.next(1, 60);
    println(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 5);
        int n;

        if (mode == 0) {
            n = rnd.any(edge);
        } else if (mode == 1) {
            n = rnd.any(primes);
        } else if (mode == 2) {
            n = rnd.any(powers);
        } else if (mode == 3) {
            n = rnd.any(composites);
        } else if (mode == 4) {
            int base = rnd.next(2, 31);
            int multiplier = rnd.next(1, 1000 / base);
            n = base * multiplier;
        } else {
            n = rnd.next(1, 1000);
        }

        println(n);
    }

    return 0;
}
