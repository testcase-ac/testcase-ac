#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read m and n
    int m = inf.readInt(1, 8, "m");
    inf.readSpace();
    // n can be up to 1e15, so use long long
    long long n = inf.readLong(1LL, 1000000000000000LL, "n");
    inf.readEoln();

    inf.readEof();
}
