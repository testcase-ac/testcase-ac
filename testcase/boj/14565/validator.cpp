#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and A according to the problem constraints
    long long N = inf.readLong(2LL, 1000000000000LL, "N");
    inf.readSpace();
    long long A = inf.readLong(1LL, N - 1, "A");
    inf.readEoln();

    // No more content after the single test case
    inf.readEof();
    return 0;
}
