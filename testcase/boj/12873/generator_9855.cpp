#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    int roll = rnd.next(1, 100);

    if (roll <= 10) {
        // Strong edge case: smallest possible N
        N = 1;
    } else if (roll <= 25) {
        // Very small N, easy to simulate by hand
        vector<int> cand = {2, 3, 4, 5, 6, 7, 8, 9, 10};
        N = rnd.any(cand);
    } else if (roll <= 40) {
        // Explicitly hit the sample cases more often
        vector<int> cand = {3, 6, 10};
        N = rnd.any(cand);
    } else if (roll <= 55) {
        // Powers of two (often tricky for circle/elimination problems)
        vector<int> cand = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
        N = rnd.any(cand);
    } else if (roll <= 70) {
        // Medium small random values
        N = rnd.next(11, 100);
    } else if (roll <= 85) {
        // Special structured numbers: cubes and near-cubes and boundaries
        vector<int> cand = {
            11, 12, 15,
            27, 64, 81, 125, 216, 343, 512, 729,
            1000, 1728, 2197, 2744, 3375,
            4095, 4999, 5000
        };
        N = rnd.any(cand);
    } else if (roll <= 95) {
        // Random moderately large
        N = rnd.next(100, 1000);
    } else {
        // Random large, to stress t^3 growth and possible overflow issues
        N = rnd.next(1000, 5000);
    }

    println(N);

    return 0;
}
