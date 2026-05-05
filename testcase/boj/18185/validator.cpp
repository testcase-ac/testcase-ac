#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 10000, "N");
    inf.readEoln();

    // Read array A of size N
    inf.readInts(N, 0, 10000, "A_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
