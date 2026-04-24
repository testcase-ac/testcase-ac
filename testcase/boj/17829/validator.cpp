#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and check its constraints
    int N = inf.readInt(2, 1024, "N");
    inf.readEoln();
    // Check N is a power of two
    ensuref((N & (N - 1)) == 0, "N (%d) is not a power of two", N);

    // Read the matrix
    for (int i = 0; i < N; i++) {
        vector<int> row = inf.readInts(N, -10000, 10000, "matrix");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
