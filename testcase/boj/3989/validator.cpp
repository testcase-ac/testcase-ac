#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: K M N
    long long K = inf.readLong(1LL, 1000000000000000000LL, "K");
    inf.readSpace();
    int M = inf.readInt(3, 1500, "M");
    inf.readSpace();
    // N can be zero up to M-1
    int N = inf.readInt(0, M - 1, "N");
    inf.readEoln();

    // Read second line: N distinct initial infected persons
    vector<int> init;
    init.reserve(N);
    if (N > 0) {
        for (int i = 0; i < N; i++) {
            int x = inf.readInt(0, M - 1, "initial");
            init.push_back(x);
            if (i + 1 < N)
                inf.readSpace();
            else
                inf.readEoln();
        }
    } else {
        // No tokens, but must still have the newline
        inf.readEoln();
    }

    // Check uniqueness of initial infected persons
    {
        set<int> seen;
        for (int i = 0; i < N; i++) {
            int x = init[i];
            ensuref(!seen.count(x),
                    "Duplicate initial infected person %d at position %d", 
                    x, i);
            seen.insert(x);
        }
    }

    inf.readEof();
    return 0;
}
