#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: L P
    int L = inf.readInt(1, 10, "L");
    inf.readSpace();
    int P = inf.readInt(1, 1000, "P");
    inf.readEoln();

    // Second line: five reported counts
    vector<int> a = inf.readInts(5, 0, 999999, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
