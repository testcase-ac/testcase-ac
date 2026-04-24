#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of marbles
    // Constraint: 2 ≤ N ≤ 1,000,000
    int N = inf.readInt(2, 1000000, "N");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
