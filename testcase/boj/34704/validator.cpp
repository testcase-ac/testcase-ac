#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read a_i
    vector<int> a = inf.readInts(N, 1, 4, "a_i");
    inf.readEoln();

    inf.readEof();
}
