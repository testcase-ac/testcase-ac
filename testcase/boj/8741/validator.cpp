#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read k: number of binary digits upper bound
    int k = inf.readInt(1, 1000000, "k");
    // Ensure no extra tokens on the line
    inf.readEoln();
    // Ensure nothing else in file
    inf.readEof();

    return 0;
}
