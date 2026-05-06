#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A: non-negative integer, no leading zeros unless it's exactly "0", length ≤ 300000
    inf.readToken("(0|[1-9][0-9]{0,299999})", "A");
    inf.readSpace();
    // Read B with the same constraints
    inf.readToken("(0|[1-9][0-9]{0,299999})", "B");
    inf.readEoln();
    inf.readEof();
    return 0;
}
