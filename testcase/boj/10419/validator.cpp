#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of queries T
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // For each query, read d and validate its range
    for (int i = 0; i < T; i++) {
        inf.readInt(1, 10000, "d");
        inf.readEoln();
    }

    // No extra content after the last line
    inf.readEof();
    return 0;
}
