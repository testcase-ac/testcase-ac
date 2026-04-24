#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m according to constraints:
    // 0 <= m <= n <= 2e9, and n != 0
    long long n = inf.readLong(1LL, 2000000000LL, "n");
    inf.readSpace();
    long long m = inf.readLong(0LL, n, "m");
    inf.readEoln();

    // No further global properties to check for this problem.

    inf.readEof();
    return 0;
}
