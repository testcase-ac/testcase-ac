#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: the number of digits (1 ≤ N ≤ 8)
    int N = inf.readInt(1, 8, "N");
    // After N there must be exactly one newline
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
