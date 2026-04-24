#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // 2. Read the string of length N, consisting of only 'R' or 'B'
    string balls = inf.readLine("[RB]{1,500000}", "balls");
    ensuref((int)balls.size() == N, "Length of balls string (%d) does not match N (%d)", (int)balls.size(), N);

    // 3. Ensure all characters are either 'R' or 'B'
    for (int i = 0; i < N; ++i) {
        ensuref(balls[i] == 'R' || balls[i] == 'B', "balls[%d] is not 'R' or 'B', but '%c'", i, balls[i]);
    }

    // 4. No further constraints: the string may be all R, all B, or mixed.

    inf.readEof();
}
