#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read the N integers
    vector<int> a = inf.readInts(N, -100, 100, "a");
    inf.readEoln();

    // Read the value v to count
    int v = inf.readInt(-100, 100, "v");
    inf.readEoln();

    // No more data
    inf.readEof();
    return 0;
}
