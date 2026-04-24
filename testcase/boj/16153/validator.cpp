#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, A, B
    int N = inf.readInt(0, 31, "N");
    inf.readSpace();
    // A and B are positive and less than 2^31
    long long A = inf.readLong(1LL, (1LL<<31) - 1, "A");
    inf.readSpace();
    long long B = inf.readLong(1LL, (1LL<<31) - 1, "B");
    inf.readEoln();

    // Read N bit indices, ensure each is in [0,30] and no duplicates
    set<int> seenBits;
    for (int i = 0; i < N; i++) {
        int bit = inf.readInt(0, 30, "bit");
        inf.readEoln();
        ensuref(!seenBits.count(bit),
                "Duplicate bit index at line %d: %d", i + 2, bit);
        seenBits.insert(bit);
    }

    // No extra data
    inf.readEof();
    return 0;
}
