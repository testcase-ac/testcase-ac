#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer N, 1 ≤ N ≤ 11, canonical decimal form
    int N = inf.readInt(1, 11, "N");
    inf.readEoln();

    // No further input
    inf.readEof();
}
