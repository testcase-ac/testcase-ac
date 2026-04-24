#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of students N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the heights A_i
    inf.readInts(N, 1, 1000, "A_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
