#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 0; i < N; i++) {
        // r: revenue without advertising
        int r = inf.readInt(-1000000, 1000000, "r");
        inf.readSpace();
        // e: revenue with advertising
        int e = inf.readInt(-1000000, 1000000, "e");
        inf.readSpace();
        // c: cost of advertising
        int c = inf.readInt(0, 1000000, "c");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
