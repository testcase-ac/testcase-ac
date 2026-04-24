#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: a natural number (>=1) up to 10^18
    long long N = inf.readLong(1LL, 1000000000000000000LL, "N");
    inf.readSpace();
    // Read K: a natural number (>=1) up to 10
    int K = inf.readInt(1, 10, "K");
    // End of the single input line
    inf.readEoln();
    // No extra content
    inf.readEof();

    return 0;
}
