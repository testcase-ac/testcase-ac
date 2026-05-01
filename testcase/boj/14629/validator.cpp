#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer N with constraints: 1 ≤ N ≤ 1,000,000,000,000
    // Canonical integer form is enforced by readLong.
    long long N = inf.readLong(1LL, 1000000000000LL, "N");
    inf.readEoln();

    inf.readEof();
}
