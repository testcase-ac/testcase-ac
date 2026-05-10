#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the three participant counts
    int P3 = inf.readInt(0, 100000, "P3");
    inf.readSpace();
    int P4 = inf.readInt(0, 100000, "P4");
    inf.readSpace();
    int P0 = inf.readInt(0, 100000, "P0");
    inf.readEoln();

    // Validate total number of participants
    long long total = (long long)P3 + P4 + P0;
    ensuref(total >= 1, "Total number of people must be at least 1, got %d+%d+%d=%lld", P3, P4, P0, total);
    ensuref(total <= 100000, "Total number of people must be at most 100000, got %lld", total);

    inf.readEof();
    return 0;
}
