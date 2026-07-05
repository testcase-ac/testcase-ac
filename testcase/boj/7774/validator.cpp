#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 100000, "m");
    inf.readEoln();

    if (n == 0) {
        if (inf.eof()) {
            ensuref(m == 0, "missing second line for n = 0 while m > 0");
            inf.readEof();
            return 0;
        }
        inf.readEoln();
    } else {
        vector<int> a = inf.readInts(n, 1, 1000, "a_i");
        inf.readEoln();
    }

    if (m == 0) {
        if (!inf.eof()) {
            inf.readEoln();
        }
    } else {
        vector<int> b = inf.readInts(m, 1, 1000, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
