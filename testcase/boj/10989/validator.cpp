#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and check its range
    long long N = inf.readLong(1LL, 10000000LL, "N");
    inf.readEoln();

    // Read each of the N numbers, one per line
    for (long long i = 0; i < N; i++) {
        inf.readInt(1, 10000, "value");
        inf.readEoln();
    }

    // No extra content after the N lines
    inf.readEof();
    return 0;
}
