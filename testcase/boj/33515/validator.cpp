#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T1 and T2 on the first (and only) line
    int T1 = inf.readInt(1, 10000, "T1");
    inf.readSpace();
    int T2 = inf.readInt(1, 10000, "T2");
    inf.readEoln();

    // No further lines allowed
    inf.readEof();
}
