#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Base price of the car
        int s = inf.readInt(1, 100000, "s");
        inf.readEoln();

        // Number of different options
        int n = inf.readInt(0, 1000, "n");
        inf.readEoln();

        // Each option: quantity q and price p
        for (int i = 0; i < n; i++) {
            int q = inf.readInt(1, 100, "q");
            inf.readSpace();
            int p = inf.readInt(1, 10000, "p");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
