#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer K, 1 <= K <= 1e9
    // Canonical form, no leading zeros, etc., is enforced by readInt.
    long long K = inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    // No further structural/global constraints given in the statement.
    // N is defined as 2023 * K but only for problem logic, not as input.

    inf.readEof();
}
