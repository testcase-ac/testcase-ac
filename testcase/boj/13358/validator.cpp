#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m according to the problem constraints
    long long n = inf.readLong(1LL, 1000000000LL, "n");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000LL, "m");
    // Ensure exactly one newline after the two numbers
    inf.readEoln();
    // Ensure nothing else follows
    inf.readEof();
    return 0;
}
