#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the five integers, each on its own line, all in [1, 10000].
    int A = inf.readInt(1, 10000, "A");
    inf.readEoln();
    int B = inf.readInt(1, 10000, "B");
    inf.readEoln();
    int C = inf.readInt(1, 10000, "C");
    inf.readEoln();
    int D = inf.readInt(1, 10000, "D");
    inf.readEoln();
    int P = inf.readInt(1, 10000, "P");
    inf.readEoln();

    // No further global constraints to check.
    inf.readEof();
    return 0;
}
