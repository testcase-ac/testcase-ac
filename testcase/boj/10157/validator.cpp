#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: C and R
    int C = inf.readInt(5, 1000, "C");
    inf.readSpace();
    int R = inf.readInt(5, 1000, "R");
    inf.readEoln();

    // Second line: K
    long long K = inf.readLong(1LL, 100000000LL, "K");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
