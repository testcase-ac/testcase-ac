#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: 1 ≤ n ≤ 1e9
    inf.readInt(1, 1000000000, "n");
    // Exactly one newline after the number
    inf.readEoln();
    // No extra input
    inf.readEof();
    return 0;
}
