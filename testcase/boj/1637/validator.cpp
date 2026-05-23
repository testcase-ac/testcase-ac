#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_VALUE = 2147483647LL;

    int N = inf.readInt(1, 20000, "N");
    inf.readEoln();

    for (int i = 0; i < N; i++) {
        long long A = inf.readLong(1LL, MAX_VALUE, "A_i");
        inf.readSpace();
        inf.readLong(A, MAX_VALUE, "C_i");
        inf.readSpace();
        inf.readLong(1LL, MAX_VALUE, "B_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
