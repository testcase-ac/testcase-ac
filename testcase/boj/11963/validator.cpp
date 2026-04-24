#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of rounds (also half the deck size for each player)
    int N = inf.readInt(2, 50000, "N");
    ensuref(N % 2 == 0, "N must be even, found %d", N);
    inf.readEoln();

    // We expect N distinct cards for Elsie, each in [1, 2N]
    vector<bool> seen(2 * N + 1, false);
    for (int i = 0; i < N; i++) {
        int card = inf.readInt(1, 2 * N, "e_i");
        inf.readEoln();
        ensuref(!seen[card],
                "Duplicate Elsie card %d at position %d", card, i + 1);
        seen[card] = true;
    }

    inf.readEof();
    return 0;
}
