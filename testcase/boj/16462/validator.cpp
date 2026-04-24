#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of students N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read N scores Q_i
    for (int i = 0; i < N; i++) {
        // Each Q_i must be an integer between 1 and 100 inclusive
        inf.readInt(1, 100, "Q_i");
        inf.readEoln();
    }

    // No extra data after the last line
    inf.readEof();
    return 0;
}
