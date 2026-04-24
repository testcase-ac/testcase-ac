#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int t = inf.readInt(1, 50, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        // Number of convenience stores
        int n = inf.readInt(0, 100, "n");
        inf.readEoln();

        // Read coordinates: house, n stores, festival
        for (int i = 0; i < n + 2; ++i) {
            int x = inf.readInt(-32768, 32767, "x");
            inf.readSpace();
            int y = inf.readInt(-32768, 32767, "y");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
