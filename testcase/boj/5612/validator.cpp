#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of minutes n
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    // Read initial number of cars in the tunnel
    // It must be non-negative. No explicit upper bound given, so we allow up to 1e9.
    long long m = inf.readLong(0LL, 1000000000LL, "m");
    inf.readEoln();

    // For each minute, read number of cars entering and leaving
    for (int i = 1; i <= n; i++) {
        int enter = inf.readInt(0, 100, "enter_i");
        inf.readSpace();
        int exit_ = inf.readInt(0, 100, "exit_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
