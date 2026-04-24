#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(2, 10);         // number of cows
    int K = rnd.next(1, 10);         // number of sessions
    double sameProb = rnd.next(0.0, 1.0);  // probability to repeat a session

    // Output K and N
    println(K, N);

    // Initial random ranking
    vector<int> ranking(N);
    iota(ranking.begin(), ranking.end(), 1);
    shuffle(ranking.begin(), ranking.end());
    println(ranking);

    // Generate remaining sessions
    for (int i = 2; i <= K; i++) {
        if (rnd.next() < sameProb) {
            // repeat previous session to boost consistency
            println(ranking);
        } else {
            // introduce a fresh random permutation
            shuffle(ranking.begin(), ranking.end());
            println(ranking);
        }
    }

    return 0;
}
