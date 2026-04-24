#include "testlib.h"
#include <vector>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int TC = 1; // Generate only one test case as requested

    println(TC); // Output the number of test cases

    // Generate parameters for the single test case
    // Keep N small for hand-checking
    int N = rnd.next(2, 10);
    // Keep M and W small
    int M = rnd.next(1, 10);
    int W = rnd.next(1, 10);
    vector<int> max_times = {10, 100, 1000, 10000};
    int max_time = rnd.any(max_times);

    println(N, M, W);

    // Generate M roads
    // Roads are bidirectional with positive weight
    for (int i = 0; i < M; ++i) {
        int S = rnd.next(1, N);
        int E = rnd.next(1, N);
        // Road time is positive
        int T = rnd.next(1, max_time);
        println(S, E, T);
    }

    // Generate W wormholes
    // Wormholes are unidirectional with non-positive weight (time decrease)
    for (int i = 0; i < W; ++i) {
        int S = rnd.next(1, N);
        int E = rnd.next(1, N);
        // Wormhole time decrease is non-negative (0 or positive)
        // The problem asks for the decrease amount T in the input.
        int T = rnd.next(0, max_time);
        println(S, E, T);
    }

    return 0;
}
