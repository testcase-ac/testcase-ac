#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Predefined small happy and unhappy seeds
    vector<int> happy = {1, 7, 10, 13, 19, 23, 28, 31, 32, 44, 68, 77, 100};
    vector<int> unhappy = {2, 3, 4, 5, 6, 8, 9, 11, 12, 14, 15, 16, 17, 18, 20};

    // Choose mode for diversity
    // 0: known happy, 1: known unhappy, 2: random by digit-length, 3: extreme max
    int mode = rnd.next(0, 3);
    long long n;
    if (mode == 0) {
        n = rnd.any(happy);
    } else if (mode == 1) {
        n = rnd.any(unhappy);
    } else if (mode == 3) {
        n = 1000000000;
    } else {
        // random number with 1 to 9 digits
        int d = rnd.next(1, 9);
        n = rnd.next(1, 9); // first digit non-zero
        for (int i = 1; i < d; i++) {
            n = n * 10 + rnd.next(0, 9);
        }
    }

    // Output single test case
    println(n);
    return 0;
}
