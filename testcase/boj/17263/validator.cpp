#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read array A of size N
    inf.readLongs(n, 0LL, 1000000000LL, "A_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
