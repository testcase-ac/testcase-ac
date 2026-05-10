#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, A, B
    int N = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int A = inf.readInt(1, 2000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 2000, "B");
    inf.readEoln();

    // Constraint: 2*B + A >= N
    ensuref(2 * B + A >= N, "Constraint violated: 2*B + A >= N, but got N=%d, A=%d, B=%d", N, A, B);

    // Read A integers: beauty of 2x1 tiles
    vector<int> beautyA = inf.readInts(A, 1, 1000000, "beautyA");
    inf.readEoln();

    // Read B integers: beauty of 2x2 tiles
    vector<int> beautyB = inf.readInts(B, 1, 1000000, "beautyB");
    inf.readEoln();

    inf.readEof();
}
