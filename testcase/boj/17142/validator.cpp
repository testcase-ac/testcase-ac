#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(4, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10, "M");
    inf.readEoln();

    // Read the lab grid
    int virusCount = 0;
    for (int i = 0; i < N; i++) {
        // Read N integers in this row
        vector<int> row = inf.readInts(N, 0, 2, "lab");
        inf.readEoln();
        for (int x : row) {
            if (x == 2) virusCount++;
        }
    }

    // Check the number of viruses constraint: M <= #2 <= 10
    ensuref(virusCount >= M,
            "The number of virus positions (2) is %d, which is less than M = %d",
            virusCount, M);
    ensuref(virusCount <= 10,
            "The number of virus positions (2) is %d, which exceeds 10",
            virusCount);

    inf.readEof();
    return 0;
}
