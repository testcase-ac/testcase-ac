#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read S and K
    string S = inf.readToken("[a-z]{1,500000}", "S");
    inf.readSpace();
    int K = inf.readInt(1, 1000000, "K");
    inf.readEoln();

    // No further constraints to check (no global property or guarantee to check).
    // S is non-empty, only lowercase, length <= 500000.
    // K is in [1, 1_000_000].

    inf.readEof();
}
