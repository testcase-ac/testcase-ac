#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(2, 1000000, "n");
    inf.readSpace();
    int k = inf.readInt(2, 1000000, "k");
    inf.readEoln();

    // Read days d_i for each friend
    inf.readInts(n, 1, 1000000, "d_i");
    inf.readEoln();

    // Read clothespins count l_i for each color
    inf.readInts(k, 1, 4000000, "l_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
