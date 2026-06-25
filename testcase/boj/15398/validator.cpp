#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readLong(1LL, 1000000000LL, "c_i");
    }
    inf.readEoln();

    string bitStringPattern = "[01]{" + to_string(n) + "," + to_string(n) + "}";
    inf.readToken(bitStringPattern, "a");
    inf.readEoln();
    inf.readToken(bitStringPattern, "b");
    inf.readEoln();
    inf.readEof();
}
