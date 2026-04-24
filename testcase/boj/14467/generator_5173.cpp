#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of observations
    int N = rnd.next(1, 20);

    // Choose a random subset of cows that actually appear
    int K = rnd.next(1, 10);
    vector<int> cows(10);
    iota(cows.begin(), cows.end(), 1);
    shuffle(cows.begin(), cows.end());
    cows.resize(K);

    // Probability to switch side on each observation
    double switchProb = rnd.next();

    // Initial positions for these cows
    vector<int> curPos(11, 0);
    for (int id : cows) {
        curPos[id] = rnd.next(0, 1);
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        int id = rnd.any(cows);
        if (rnd.next() < switchProb) {
            curPos[id] = 1 - curPos[id];
        }
        println(id, curPos[id]);
    }

    return 0;
}
