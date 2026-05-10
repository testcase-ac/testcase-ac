#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 1 ≤ N ≤ 500000
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // No more tokens
    inf.readEof();
    return 0;
}
