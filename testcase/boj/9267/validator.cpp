#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read a, b, S with exact whitespace separators
    long long a = inf.readLong(0LL, 1000000000000000000LL, "a");
    inf.readSpace();
    long long b = inf.readLong(0LL, 1000000000000000000LL, "b");
    inf.readSpace();
    long long S = inf.readLong(0LL, 1000000000000000000LL, "S");
    inf.readEoln();

    inf.readEof();
    return 0;
}
