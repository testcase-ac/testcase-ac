#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: skewed between 2 and 10
    int tN = rnd.next(-1, 1);
    int N = rnd.wnext(9, tN) + 2;  // yields [2,10]

    // Decide if all K_i should be <= N or allow some > N
    bool allSmall = rnd.next() < 0.7;
    int highLimit;
    if (allSmall) {
        highLimit = N;
    } else {
        int maxHL = min(1000, N + 20);
        highLimit = rnd.next(N + 1, maxHL);
    }

    // Build pool of candidate K_i values
    vector<int> cand;
    for (int k = 2; k <= highLimit; ++k) {
        cand.push_back(k);
    }

    // Determine M with a small size, 1 <= M < N
    int maxM = min((int)cand.size(), N - 1);
    int tM = rnd.next(-1, 1);
    int M = min(maxM, rnd.wnext(maxM, tM) + 1); // yields [1, maxM]

    // Sample M distinct K_i and sort them
    shuffle(cand.begin(), cand.end());
    vector<int> K(cand.begin(), cand.begin() + M);
    sort(K.begin(), K.end());

    // Output
    println(N, M);
    println(K);
    return 0;
}
