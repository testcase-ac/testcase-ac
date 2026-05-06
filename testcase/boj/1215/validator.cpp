#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k with the given bounds
    long long n = inf.readLong(1LL, 1000000000LL, "n");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000LL, "k");
    inf.readEoln();

    // Ensure no extra input
    inf.readEof();
    return 0;
}
