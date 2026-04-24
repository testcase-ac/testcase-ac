#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Read N rows each with M integers
    for (int i = 0; i < N; i++) {
        // read exactly M integers in [0,100000]
        vector<int> row = inf.readInts(M, 0, 100000, "silver");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
