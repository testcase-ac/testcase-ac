#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and S
    int N = inf.readInt(10, 99999, "N");
    inf.readSpace();
    int S = inf.readInt(1, 100000000, "S");
    inf.readEoln();

    // Read the sequence of length N
    vector<int> a = inf.readInts(N, 1, 10000, "a_i");
    inf.readEoln();

    // End of file
    inf.readEof();
    return 0;
}
