#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: 0 ≤ n ≤ 20
    int n = inf.readInt(0, 20, "n");
    inf.readEoln();

    // No extra input
    inf.readEof();
    return 0;
}
