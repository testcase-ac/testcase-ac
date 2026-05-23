#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        for (int digit = 0; digit < 10; ++digit) {
            inf.readInt(0, 1, format("available_%d_%d", tc, digit).c_str());
            if (digit < 9) inf.readSpace();
        }
        inf.readEoln();

        inf.readInt(1, 100, "X");
        inf.readEoln();
    }

    inf.readEof();
}
