#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N with constraint 0 ≤ N ≤ 12
    int N = inf.readInt(0, 12, "N");
    inf.readEoln();

    // No extra input
    inf.readEof();
    return 0;
}
