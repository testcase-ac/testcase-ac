#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 500000;
    const long long MAX_VALUE = 1000000000LL;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    inf.readLong(1LL, MAX_VALUE, "X");
    inf.readEoln();

    inf.readLongs(n, 1LL, MAX_VALUE, "A_i");
    inf.readEoln();

    inf.readLongs(n, 1LL, MAX_VALUE, "B_i");
    inf.readEoln();

    inf.readEof();
}
