#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, X
    int N = inf.readInt(3, 100, "N");
    inf.readSpace();
    int X = inf.readInt(1, 100, "X");
    inf.readEoln();

    // Second line: T_1 ... T_N
    vector<int> T = inf.readInts(N, 1, 200, "T_i");
    inf.readEoln();

    // The problem guarantees that "the first person to drink" exists.
    // Validate this by simulating until some player exceeds their limit.
    // Voice height is non-decreasing and T_i <= 200, so if no one loses
    // within one full cycle, then no one will ever lose.
    int firstDrinker = -1;
    int maxRounds = N; // enough to detect impossibility
    long long voice = X;
    for (int step = 0; step < 1LL * N * maxRounds; ++step) {
        int i = step % N; // player index 0..N-1
        if (voice > T[i]) {
            firstDrinker = i + 1;
            break;
        }
        voice++;
    }

    ensuref(firstDrinker != -1,
            "No one ever drinks: for given N, X, and T_i, no player exceeds their limit.");

    inf.readEof();
}
