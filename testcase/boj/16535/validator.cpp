#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    // 2. Read the sequence of balls
    vector<int> balls = inf.readInts(N, 1, 1000000, "balls");
    inf.readEoln();

    // 3. Check that every two consecutive balls have different numbers
    for (int i = 1; i < N; ++i) {
        ensuref(balls[i] != balls[i-1],
            "Consecutive balls at positions %d and %d have the same number: %d",
            i, i+1, balls[i]);
    }

    inf.readEof();
}
