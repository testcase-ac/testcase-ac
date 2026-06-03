#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The Korean original for BOJ 2201 has one K, while the bundled
    // English variant describes T test cases. This validator follows the
    // original BOJ input format and the repository's existing sample/solution.
    inf.readLong(1LL, 1000000000000000000LL, "K");
    inf.readEoln();
    inf.readEof();
}
