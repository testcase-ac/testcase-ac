#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the desired recursion depth N, must satisfy 1 ≤ N ≤ 50
    int N = inf.readInt(1, 50, "N");
    // After the integer, there should be exactly one end-of-line
    inf.readEoln();
    // And immediately EOF
    inf.readEof();

    return 0;
}
