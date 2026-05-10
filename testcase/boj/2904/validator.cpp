#include "testlib.h"
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read N numbers
    vector<int> A = inf.readInts(N, 1, 1000000, "A_i");
    inf.readEoln();

    // No further constraints in the statement.
    // But let's check for unnecessary leading zeros in input numbers.
    // Since readInts reads as int, we need to check the original tokens for leading zeros.
    // We'll re-read the line as a string and check each token.
    // (But since readInts already consumed the line, we cannot do this here.)
    // So, we need to check only the value range, as readInts already does.

    inf.readEof();
}
