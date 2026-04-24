#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int LINES = 28;
    set<int> seen;
    for (int i = 0; i < LINES; i++) {
        int x = inf.readInt(1, 30, "n_i");
        inf.readEoln();
        ensuref(!seen.count(x),
                "Duplicate attendance number at line %d: %d", i+1, x);
        seen.insert(x);
    }

    // After reading exactly 28 lines, there must be nothing else.
    inf.readEof();
    return 0;
}
