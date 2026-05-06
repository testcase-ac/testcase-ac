#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    long long n = inf.readLong(6LL, 10000000000000LL, "n");
    inf.readEoln();

    inf.readEof();
}
