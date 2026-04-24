#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read array A of size N
    inf.readLongs(n, -2147483648LL, 2147483647LL, "A_i");
    inf.readEoln();

    // Read M
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read queries B of size M
    inf.readLongs(m, -2147483648LL, 2147483647LL, "B_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
