#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, S, R
    int N = inf.readInt(2, 10, "N");
    inf.readSpace();
    int S = inf.readInt(1, N, "S");
    inf.readSpace();
    int R = inf.readInt(1, N, "R");
    inf.readEoln();

    // Read broken team numbers
    vector<int> broken = inf.readInts(S, 1, N, "broken_i");
    inf.readEoln();

    // Read extra team numbers
    vector<int> extra = inf.readInts(R, 1, N, "extra_i");
    inf.readEoln();

    // Check duplicates in broken list
    {
        set<int> seen;
        for (int i = 0; i < S; i++) {
            int x = broken[i];
            ensuref(!seen.count(x),
                    "Duplicate team %d in broken list at position %d", x, i+1);
            seen.insert(x);
        }
    }

    // Check duplicates in extra list
    {
        set<int> seen;
        for (int i = 0; i < R; i++) {
            int x = extra[i];
            ensuref(!seen.count(x),
                    "Duplicate team %d in extra list at position %d", x, i+1);
            seen.insert(x);
        }
    }

    // Final EOF check
    inf.readEof();
    return 0;
}
