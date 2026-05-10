#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(0, 10000, "n");
    inf.readEoln();

    // If n == 0, there should be no more lines
    if (n == 0) {
        inf.readEof();
        return 0;
    }

    // For each university, read p and d
    for (int i = 0; i < n; ++i) {
        int p = inf.readInt(1, 10000, "p");
        inf.readSpace();
        int d = inf.readInt(1, 10000, "d");
        inf.readEoln();
        // No further constraints on p and d (they can be equal or not)
    }

    inf.readEof();
}
