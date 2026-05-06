#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer n: must be a natural number (1 ≤ n ≤ 90)
    int n = inf.readInt(1, 90, "n");
    // After n, there must be exactly one end‐of‐line
    inf.readEoln();
    // And then immediately EOF
    inf.readEof();
    return 0;
}
