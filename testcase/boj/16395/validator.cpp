#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k with given constraints
    int n = inf.readInt(1, 30, "n");
    inf.readSpace();
    int k = inf.readInt(1, 30, "k");
    inf.readEoln();

    // Ensure k is not greater than n
    ensuref(k <= n, "k (%d) must be <= n (%d)", k, n);

    // No more input
    inf.readEof();
    return 0;
}
