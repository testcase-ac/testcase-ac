#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer s, with 1 <= s <= 1e9
    long long s = inf.readLong(1LL, 1000000000LL, "s");
    inf.readEoln();

    inf.readEof();
    return 0;
}
