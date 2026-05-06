#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer N (1 ≤ N ≤ 10^18)
    long long N = inf.readLong(1LL, 1000000000000000000LL, "N");
    // There must be exactly one newline after N
    inf.readEoln();
    // No extra content
    inf.readEof();

    return 0;
}
