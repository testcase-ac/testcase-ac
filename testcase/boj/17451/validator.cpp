#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of segments n (1 ≤ n ≤ 3·10^5)
    int n = inf.readInt(1, 300000, "n");
    inf.readEoln();

    // Read the required speeds v_1 ... v_n, each in [1, 10^9]
    inf.readInts(n, 1, 1000000000, "v");
    inf.readEoln();

    // No more content
    inf.readEof();
    return 0;
}
