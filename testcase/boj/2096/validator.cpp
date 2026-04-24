#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of rows
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // For each of the N rows, read exactly three integers in [0,9]
    for (int i = 1; i <= N; i++) {
        vector<int> row = inf.readInts(3, 0, 9, "value");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
