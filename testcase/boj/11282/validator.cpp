#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer N on the first line, 1 ≤ N ≤ 11172
    int N = inf.readInt(1, 11172, "N");
    inf.readEoln();

    // No further input
    inf.readEof();
}
