#include "testlib.h"
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a type of test case for diversity
    // 0: very small S
    // 1: S just below a triangular number
    // 2: S exactly triangular
    // 3: S near the maximum limit
    // 4: random medium S
    int type = rnd.next(0, 4);
    unsigned long long S;

    if (type == 0) {
        // very small S: 1 to 10
        S = rnd.next(1, 10);
    }
    else if (type == 1) {
        // just below a triangular number for n in [2,20]
        int n = rnd.next(2, 20);
        unsigned long long tri = (unsigned long long)n * (n + 1) / 2;
        S = tri - 1;
    }
    else if (type == 2) {
        // exactly a triangular number for n in [1,20]
        int n = rnd.next(1, 20);
        S = (unsigned long long)n * (n + 1) / 2;
    }
    else if (type == 3) {
        // near the maximum of 2^32-1
        int dec = rnd.next(0, 100);
        S = 4294967295ULL - dec;
    }
    else {
        // random medium S up to 10000
        S = rnd.next(1, 10000);
    }

    // Output the single test case
    println(S);
    return 0;
}
