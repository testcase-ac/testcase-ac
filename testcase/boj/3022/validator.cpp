#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of pieces taken
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Each of the following N lines: a child's name (1 to 20 lowercase letters)
    for (int i = 0; i < N; i++) {
        // Read exactly one token matching lowercase letters of length [1,20]
        inf.readToken("[a-z]{1,20}", "name");
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
