#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read m and n
    int m = inf.readInt(1, 500, "m");
    inf.readSpace();
    int n = inf.readInt(1, 500, "n");
    inf.readEoln();

    // Read n lines of preferences, each with m non-negative integers <= 1e6
    for (int i = 0; i < n; i++) {
        vector<int> prefs = inf.readInts(m, 0, 1000000, "preference");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
