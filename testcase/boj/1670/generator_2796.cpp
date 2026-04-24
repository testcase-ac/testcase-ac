#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a scenario type for diverse N values
    // min: smallest even N, small: 2..20, medium: 12..100, large: 1000..10000, max: 10000
    string mode = rnd.next("min|small|medium|large|max");
    int N;
    if (mode == "min") {
        N = 2;
    } else if (mode == "small") {
        // small even N from 2 up to 20
        N = rnd.next(1, 10) * 2;
    } else if (mode == "medium") {
        // medium even N from 12 up to 100
        N = rnd.next(6, 50) * 2;
    } else if (mode == "large") {
        // large even N from 1000 up to 10000
        N = rnd.next(500, 5000) * 2;
    } else {
        // max boundary
        N = 10000;
    }

    // Output a single test case: one even integer N <= 10000
    println(N);
    return 0;
}
