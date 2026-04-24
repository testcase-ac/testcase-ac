#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of days
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read N counter values a_i
    inf.readInts(N, 0, 100, "a");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
