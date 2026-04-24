#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: n and k
    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int maxk = (n - 1 < 200 ? n - 1 : 200);
    int k = inf.readInt(1, maxk, "k");
    inf.readEoln();

    // Second line: n non-negative integers a_i
    inf.readInts(n, 0, 10000, "a_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
