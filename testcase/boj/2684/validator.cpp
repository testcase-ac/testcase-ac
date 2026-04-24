#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases P
    int P = inf.readInt(1, 1000, "P");
    inf.readEoln();

    // For each test case, read exactly 40 characters, each 'H' or 'T'
    for (int i = 0; i < P; i++) {
        inf.readToken("[HT]{40}", "s");
        inf.readEoln();
    }

    // No extra characters after the last newline
    inf.readEof();
    return 0;
}
