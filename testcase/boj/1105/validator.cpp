#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L and R on one line: 1 <= L <= R <= 2e9
    long long L = inf.readLong(1LL, 2000000000LL, "L");
    inf.readSpace();
    long long R = inf.readLong(L, 2000000000LL, "R");
    inf.readEoln();

    inf.readEof();
    return 0;
}
