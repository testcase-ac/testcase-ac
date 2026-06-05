#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> boundary = {1, 2, 3, 4, 5, 6, 10, 11, 12, 99, 100, 999, 1000, 2699, 2700};
    vector<int> primes = {7, 11, 13, 17, 19, 101, 997, 1543, 2699};
    vector<int> primePowers = {8, 9, 16, 25, 27, 32, 49, 81, 121, 625};
    vector<int> twoPrimeFactors = {6, 10, 12, 14, 15, 18, 21, 22, 26, 35, 77, 143, 221, 899};
    vector<int> manyPrimeFactors = {30, 42, 60, 66, 70, 84, 90, 105, 210, 330, 390, 2310};
    vector<int> digitPatterns = {
        1001, 1010, 1100, 1111, 1234, 1299, 1999, 2000, 2001, 2025, 2199, 2499, 2599, 2699
    };

    int mode = rnd.next(0, 8);
    int n;
    if (mode == 0) {
        n = rnd.any(boundary);
    } else if (mode == 1) {
        n = rnd.any(primes);
    } else if (mode == 2) {
        n = rnd.any(primePowers);
    } else if (mode == 3) {
        n = rnd.any(twoPrimeFactors);
    } else if (mode == 4) {
        n = rnd.any(manyPrimeFactors);
    } else if (mode == 5) {
        n = rnd.any(digitPatterns);
    } else if (mode == 6) {
        n = rnd.next(1, 50);
    } else if (mode == 7) {
        n = rnd.next(51, 999);
    } else {
        n = rnd.next(1000, 2700);
    }

    println(n);
    return 0;
}
