#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    long long M = inf.readLong(1LL, 10000000000LL, "M");
    inf.readEoln();

    inf.readEof();
}
