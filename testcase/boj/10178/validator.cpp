#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases, assume up to 100000 if not specified
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int i = 0; i < t; i++) {
        setTestCase(i + 1);

        // c: number of candies, v: number of siblings
        int c = inf.readInt(1, 1000, "c_i");
        inf.readSpace();
        int v = inf.readInt(1, 1000, "v_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
