#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case as per statement.
    // First line: N and K (natural numbers)
    // Constraints: 1 ≤ N ≤ 10^6, 1 ≤ K ≤ 10^9
    long long N = inf.readLong(1LL, 1000000LL, "N");
    inf.readSpace();
    long long K = inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    // No further lines; output is not part of the input file
    inf.readEof();
}
