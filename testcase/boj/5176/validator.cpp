#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases K, assume up to 100000 if not specified
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    for (int t = 1; t <= K; t++) {
        setTestCase(t);

        // Read P and M
        int P = inf.readInt(1, 500, "P");
        inf.readSpace();
        int M = inf.readInt(1, 500, "M");
        inf.readEoln();

        // Each of the next P lines is a desired seat in [1, M]
        for (int i = 1; i <= P; i++) {
            char buf[20];
            sprintf(buf, "seat_%d", i);
            inf.readInt(1, M, buf);
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
