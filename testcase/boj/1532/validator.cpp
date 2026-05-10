#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: G1 S1 B1
    int G1 = inf.readInt(0, 1000000, "G1");
    inf.readSpace();
    int S1 = inf.readInt(0, 1000000, "S1");
    inf.readSpace();
    int B1 = inf.readInt(0, 1000000, "B1");
    inf.readEoln();

    // Read second line: G2 S2 B2
    int G2 = inf.readInt(0, 1000000, "G2");
    inf.readSpace();
    int S2 = inf.readInt(0, 1000000, "S2");
    inf.readSpace();
    int B2 = inf.readInt(0, 1000000, "B2");
    inf.readEoln();

    inf.readEof();
}
