#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // For each test case, read a and b
    for (int i = 0; i < T; i++) {
        int a = inf.readInt(0, 100, "a");
        inf.readSpace();
        int b = inf.readInt(0, 64, "b");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
