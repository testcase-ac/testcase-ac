#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 97, 997, 999983};
    vector<int> powers = {4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 256, 512, 729, 1024};
    vector<int> composites = {6, 10, 12, 18, 24, 30, 36, 60, 72, 120, 210, 360,
                              840, 1260, 2520, 5040, 7560, 83160, 720720, 1000000};

    int z = rnd.next(1, 10);
    println(z);

    for (int tc = 0; tc < z; ++tc) {
        int mode = rnd.next(0, 6);
        int n;

        if (mode == 0) {
            n = rnd.next(1, 20);
        } else if (mode == 1) {
            n = rnd.any(primes);
        } else if (mode == 2) {
            n = rnd.any(powers);
        } else if (mode == 3) {
            n = rnd.any(composites);
        } else if (mode == 4) {
            int base = rnd.next(1, 1000);
            n = base * rnd.next(1, 1000);
        } else {
            n = rnd.next(999000, 1000000);
        }

        println(n);
    }

    return 0;
}
