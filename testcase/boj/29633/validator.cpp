#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M: number of N cases (2 ≤ M ≤ 200)
    int M = inf.readInt(2, 200, "M");
    inf.readEoln();

    // Read K: number of students (2 ≤ K ≤ 50)
    int K = inf.readInt(2, 50, "K");
    inf.readEoln();

    // no further input
    inf.readEof();
    return 0;
}
