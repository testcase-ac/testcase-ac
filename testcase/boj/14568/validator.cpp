#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: total number of candies.
    // Constraint: 1 ≤ N ≤ 100
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    inf.readEof();
    return 0;
}
