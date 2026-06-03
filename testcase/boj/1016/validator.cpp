#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long minValue = inf.readLong(1LL, 1000000000000LL, "min");
    inf.readSpace();
    long long maxValue = inf.readLong(minValue, minValue + 1000000LL, "max");
    inf.readEoln();

    inf.readEof();
    return 0;
}
