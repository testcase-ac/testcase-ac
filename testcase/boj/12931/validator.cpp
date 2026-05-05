#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read B[0..N-1]
    vector<int> B = inf.readInts(N, 0, 1000, "B_i");
    inf.readEoln();

    // No further constraints in the problem statement.
    // But let's check for unnecessary leading zeros in B (e.g., "001" is not allowed)
    // Since readInts reads as int, we cannot check leading zeros here.
    // But if the problem says "as string", we would have to check.

    inf.readEof();
}
