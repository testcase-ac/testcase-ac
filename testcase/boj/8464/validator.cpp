#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // Read the single input integer n
    long long n = inf.readLong(1LL, 10000000000LL, "n");
    // Ensure exactly one newline after the integer
    inf.readEoln();
    // Ensure no extra content after this line
    inf.readEof();
    return 0;
}
