#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const long long MAX_A = 1500000000LL;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readEoln();

    vector<long long> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readLong(1LL, MAX_A, "a_i");
        if (i + 1 < n) inf.readSpace();
    }
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        b[i] = inf.readLong(1LL, MAX_A, "b_i");
        if (i + 1 < n) inf.readSpace();
    }
    inf.readEoln();

    inf.readEof();
}
