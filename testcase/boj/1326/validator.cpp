#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of stones N
    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Read the values on the stones
    vector<int> stones = inf.readInts(n, 1, 10000, "stone_value");
    inf.readEoln();

    // Read start and end positions a, b
    int a = inf.readInt(1, n, "a");
    inf.readSpace();
    int b = inf.readInt(1, n, "b");
    inf.readEoln();

    // End of file
    inf.readEof();
    return 0;
}
