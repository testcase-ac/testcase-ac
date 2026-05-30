#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_N = 9000000000000000000LL;

    long long a = inf.readLong(1LL, MAX_N, "a");
    inf.readSpace();
    long long b = inf.readLong(a, MAX_N, "b");
    inf.readEoln();

    inf.readEof();
    return 0;
}
