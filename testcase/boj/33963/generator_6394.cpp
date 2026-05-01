#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Precompute powers of 10 up to 10^9
    long long pows[10] = {
        1LL, 10LL, 100LL, 1000LL, 10000LL,
        100000LL, 1000000LL, 10000000LL, 100000000LL, 1000000000LL
    };

    // Choose digit count D in [1,9] so that N has D digits
    int D = rnd.next(1, 9);
    long long low = pows[D - 1];
    long long high = pows[D] - 1; // <= 10^9 - 1

    // Pick one of several patterns to expose edge cases
    int choice = rnd.next(0, 5);
    long long N;
    switch (choice) {
        case 0:
            // the smallest D-digit number
            N = low;
            break;
        case 1:
            // the largest D-digit number
            N = high;
            break;
        case 2:
            // a mid-threshold value 5 * 10^(D-1), if valid
            if (D >= 2) N = low * 5;
            else N = rnd.next(low, high);
            break;
        case 3:
            // near the upper boundary
            if (high - low >= 10) N = rnd.next(high - 10, high);
            else N = rnd.next(low, high);
            break;
        case 4:
            // in the low doubling zone [low, min(low*2, high)]
            {
                long long h2 = (low * 2 <= high ? low * 2 : high);
                N = rnd.next(low, h2);
            }
            break;
        case 5:
        default:
            // uniform random in [low, high]
            N = rnd.next(low, high);
            break;
    }

    // Output a single N
    println(N);
    return 0;
}
