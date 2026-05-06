#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: 2 ≤ n ≤ 500,000
    inf.readInt(2, 500000, "n");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
