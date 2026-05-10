#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read a_1 ... a_N
    vector<int> a = inf.readInts(N, -10000, 10000, "a_i");
    inf.readEoln();

    inf.readEof();
}
