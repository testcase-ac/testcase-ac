#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const long long MAX_AB = 1000000000LL;

    int N = inf.readInt(1, MAX_N, "N");
    inf.readEoln();

    // Read N lines of (a_i, b_i)
    for (int i = 0; i < N; ++i) {
        long long a = inf.readLong(0LL, MAX_AB, "a_i");
        inf.readSpace();
        long long b = inf.readLong(0LL, MAX_AB, "b_i");
        inf.readEoln();
        (void)a;
        (void)b;
    }

    inf.readEof();
}
