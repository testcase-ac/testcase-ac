#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 1 ≤ N ≤ 2^30
    int N = inf.readInt(1, 1 << 30, "N");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
