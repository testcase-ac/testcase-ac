#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer n: 1 ≤ n ≤ 100000
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();  // exactly one newline after n

    inf.readEof();   // no extra characters after the newline
    return 0;
}
