#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T
    int T = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        // Read a and b
        int a = inf.readInt(1, 50000, "a");
        inf.readSpace();
        int b = inf.readInt(1, 50000, "b");
        inf.readEoln();
    }

    inf.readEof();
}
