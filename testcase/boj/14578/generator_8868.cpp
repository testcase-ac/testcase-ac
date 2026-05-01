#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    int mode = rnd.next(0, 11); // 12 modes: 0..11

    if (mode <= 3) {
        // Strong bias towards very small explicit values
        static vector<int> small = {1, 2, 3, 3, 4, 5};
        N = rnd.any(small);
    } else if (mode <= 6) {
        // General small range, easy to verify by hand
        N = rnd.next(2, 15);
    } else if (mode == 7) {
        // Small/medium
        N = rnd.next(16, 40);
    } else if (mode == 8) {
        // Medium
        N = rnd.next(41, 200);
    } else if (mode == 9) {
        // Medium/large but still manageable
        N = rnd.next(201, 2000);
    } else if (mode == 10) {
        // Large range up to upper bound
        N = rnd.next(2001, 100000);
    } else {
        // Hand-picked interesting values: tiny, moderate, and extremes
        static vector<int> special = {1, 2, 3, 4, 5, 10, 11, 12, 50, 100, 999, 1000, 9999, 100000};
        N = rnd.any(special);
    }

    println(N);
    return 0;
}
