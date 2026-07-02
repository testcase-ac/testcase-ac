#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

static long long minMovesToState(const string& state) {
    long long moves = 0;
    char source = 'A';

    for (int disk = static_cast<int>(state.size()) - 1; disk >= 0; --disk) {
        char pos = state[disk];
        if (pos != source) {
            moves += 1LL << disk;
            source = static_cast<char>('A' + 'B' + 'C' - source - pos);
        }
    }

    return moves;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 30, "n");
    inf.readSpace();
    long long maxMoves = (1LL << n) - 1;
    long long m = inf.readLong(0LL, maxMoves, "m");
    inf.readEoln();

    string state = inf.readToken("[ABC]{1,30}", "state");
    inf.readEoln();
    ensuref(static_cast<int>(state.size()) == n,
            "state length must be n: got %d, expected %d",
            static_cast<int>(state.size()), n);

    long long requiredMoves = minMovesToState(state);
    ensuref(m <= requiredMoves,
            "m must not exceed minimum moves to target state: got %lld, required upper bound %lld",
            m, requiredMoves);

    inf.readEof();
}
