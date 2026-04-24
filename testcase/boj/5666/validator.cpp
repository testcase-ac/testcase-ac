#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    // Read until EOF: each line is one test case
    while (!inf.eof()) {
        // Read H and P with strict spacing: "H P\n"
        int H = inf.readInt(1, 1000, "H");
        inf.readSpace();
        int P = inf.readInt(1, 1000, "P");
        inf.readEoln();

        tc++;
        ensuref(tc <= 100000, "Too many test cases: %d (limit is 100000)", tc);
    }

    ensuref(tc > 0, "No test cases found");

    inf.readEof();
    return 0;
}
