#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: size of the sequence
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the sequence A of length N, each between 1 and 1000
    inf.readInts(N, 1, 1000, "A");
    inf.readEoln();

    // No extra content
    inf.readEof();
    return 0;
}
