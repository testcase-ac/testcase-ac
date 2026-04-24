#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer K
    long long K = inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
