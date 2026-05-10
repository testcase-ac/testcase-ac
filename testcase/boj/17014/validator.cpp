#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // Read each N_i
    for (int i = 0; i < T; i++) {
        int N = inf.readInt(4, 1000000, "N_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
