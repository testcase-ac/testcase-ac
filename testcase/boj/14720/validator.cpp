#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of stores
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the sequence of milk types
    vector<int> milk = inf.readInts(N, 0, 2, "milk_i");
    inf.readEoln();

    // No more tokens
    inf.readEof();
    return 0;
}
