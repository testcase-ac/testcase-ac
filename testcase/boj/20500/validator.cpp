#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of digits
    int N = inf.readInt(1, 1515, "N");
    inf.readEoln();      // End of the only line
    inf.readEof();       // No extra content
    return 0;
}
