#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The input file contains a single integer number n — the index of Peter’s ATE (100 ≤ n ≤ 999).
    int n = inf.readInt(100, 999, "n");
    inf.readEoln();

    // No further constraints or global properties to check.

    inf.readEof();
}
