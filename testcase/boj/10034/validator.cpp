#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read starting mileage X: 100 <= X <= 1e18
    long long X = inf.readLong(100LL, 1000000000000000000LL, "X");
    inf.readSpace();
    // Read ending mileage Y: X <= Y <= 1e18
    long long Y = inf.readLong(X, 1000000000000000000LL, "Y");
    inf.readEoln();
    inf.readEof();

    return 0;
}
