#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    long long N = inf.readLong(-1000000000000LL, 1000000000000LL, "N");
    inf.readEoln();

    inf.readEof();
}
