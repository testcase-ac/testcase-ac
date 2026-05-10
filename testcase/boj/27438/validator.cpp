#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 1 ≤ N ≤ 13,559,699
    int N = inf.readInt(1, 13559699, "N");
    inf.readEoln();
    inf.readEof();
    return 0;
}
