#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        // Read x
        int x = inf.readInt(0, 99999999, "x");
        inf.readEoln();
    }

    inf.readEof();
}
