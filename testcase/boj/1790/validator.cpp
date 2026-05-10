#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and k on a single line
    int N = inf.readInt(1, 100000000, "N");
    inf.readSpace();  // at least one whitespace
    long long k = inf.readLong(1LL, 1000000000LL, "k");
    inf.readEoln();

    inf.readEof();
    return 0;
}
