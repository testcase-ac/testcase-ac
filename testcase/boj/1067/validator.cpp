#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int n = inf.readInt(1, 60000, "N");
    inf.readEoln();

    // Read sequence X of length N, each element in [0,100]
    inf.readInts(n, 0, 100, "X_i");
    inf.readEoln();

    // Read sequence Y of length N, each element in [0,100]
    inf.readInts(n, 0, 100, "Y_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
