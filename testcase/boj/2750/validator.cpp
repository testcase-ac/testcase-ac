#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of elements
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the N integers, each in its own line, and check for duplicates
    set<int> seen;
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(-1000, 1000, "a_i");
        inf.readEoln();
        ensuref(!seen.count(x),
                "Duplicate number at line %d: %d",
                i + 2, x);
        seen.insert(x);
    }

    inf.readEof();
    return 0;
}
