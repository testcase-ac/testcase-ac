#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K: the rank of the favorite number (1 ≤ K ≤ 1e9)
    long long K = inf.readLong(1LL, 1000000000LL, "K");
    // After K there must be exactly one newline (no extra spaces)
    inf.readEoln();

    // No more tokens
    inf.readEof();
    return 0;
}
