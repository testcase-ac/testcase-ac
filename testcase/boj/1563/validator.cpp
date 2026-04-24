#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of days in a semester, must be between 1 and 1000 inclusive.
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // No more content
    inf.readEof();
    return 0;
}
