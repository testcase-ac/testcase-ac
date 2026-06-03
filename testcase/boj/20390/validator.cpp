#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_VALUE = 1000000000000LL;

    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    long long a = inf.readLong(0LL, MAX_VALUE, "A");
    inf.readSpace();
    long long b = inf.readLong(0LL, MAX_VALUE, "B");
    inf.readSpace();
    long long c = inf.readLong(1LL, MAX_VALUE, "C");
    inf.readSpace();
    long long d = inf.readLong(0LL, MAX_VALUE, "D");
    inf.readEoln();

    vector<long long> x = inf.readLongs(n, 0LL, MAX_VALUE, "X_i");
    inf.readEoln();

    inf.readEof();
}
