#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of lines parameter (1 ≤ N ≤ 100)
    inf.readInt(1, 100, "N");
    // After N there must be exactly one newline
    inf.readEoln();
    // No extra tokens; file must end here
    inf.readEof();
    return 0;
}
