#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read four positive integers, each on its own line
    long long t1 = inf.readLong(1LL, 3599LL, "t1");
    inf.readEoln();
    long long t2 = inf.readLong(1LL, 3599LL, "t2");
    inf.readEoln();
    long long t3 = inf.readLong(1LL, 3599LL, "t3");
    inf.readEoln();
    long long t4 = inf.readLong(1LL, 3599LL, "t4");
    inf.readEoln();

    // Total travel time must be between 1 minute (60s) and 59 minutes 59 seconds (3599s)
    long long total = t1 + t2 + t3 + t4;
    ensuref(total >= 60 && total <= 3599,
            "Total time %lld is out of range [60,3599]", total);

    inf.readEof();
    return 0;
}
