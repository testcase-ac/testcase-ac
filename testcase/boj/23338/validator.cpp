#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read p and q
    long long p = inf.readLong(1LL, 1000000000000000000LL, "p");
    inf.readSpace();
    long long q = inf.readLong(1LL, p, "q");
    inf.readEoln();

    inf.readEof();
}
