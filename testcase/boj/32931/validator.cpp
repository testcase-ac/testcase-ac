#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 200000, "N");
    inf.readEoln();

    // Read first row
    vector<int> row1 = inf.readInts(N, -1000000000, 1000000000, "a_1j");
    inf.readEoln();

    // Read second row
    vector<int> row2 = inf.readInts(N, -1000000000, 1000000000, "a_2j");
    inf.readEoln();

    inf.readEof();
}
