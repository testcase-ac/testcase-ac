#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 15000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 15000000, "M");
    inf.readEoln();

    // No further constraints to check

    inf.readEof();
}
