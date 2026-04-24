#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: a natural number, 1 ≤ N ≤ 100,000,000,000,000
    long long N = inf.readLong(1LL, 100000000000000LL, "N");
    // After N there must be exactly one end-of-line, with no extra spaces
    inf.readEoln();
    // No extra content after the single line
    inf.readEof();

    return 0;
}
