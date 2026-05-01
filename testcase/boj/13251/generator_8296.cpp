#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for number of colors M: bias small/medium/large
    vector<int> tMs = {-3, -1, 1, 3};
    int tM = rnd.any(tMs);
    int M = rnd.wnext(10, tM) + 1; // M in [1..10]

    // Hyper-parameter scenario for counts: uniform small, small skewed, uniform large, large skewed
    vector<int> scenarios = {0, 1, 2, 3};
    int scenario = rnd.any(scenarios);

    vector<int> counts(M);
    if (scenario == 0) {
        // uniform small counts [1,5]
        for (int i = 0; i < M; i++)
            counts[i] = rnd.next(1, 5);
    } else if (scenario == 1) {
        // one large, rest small
        int idx = rnd.next(0, M - 1);
        for (int i = 0; i < M; i++)
            counts[i] = (i == idx ? rnd.next(10, 50) : rnd.next(1, 5));
    } else if (scenario == 2) {
        // uniform large counts [10,50]
        for (int i = 0; i < M; i++)
            counts[i] = rnd.next(10, 50);
    } else {
        // one very large, rest medium
        int idx = rnd.next(0, M - 1);
        for (int i = 0; i < M; i++)
            counts[i] = (i == idx ? rnd.next(30, 50) : rnd.next(10, 20));
    }

    // Total pebbles
    int N = accumulate(counts.begin(), counts.end(), 0);

    // Hyper-parameter for K: bias towards small, mid, large
    vector<int> tKs = {-2, -1, 0, 1, 2};
    int tK = rnd.any(tKs);
    int K = rnd.wnext(N, tK) + 1; // K in [1..N]

    // Output
    println(M);
    println(counts);
    println(K);

    return 0;
}
