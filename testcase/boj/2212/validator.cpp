#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of sensors
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Read number of base stations
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    // Read sensor positions
    for (int i = 0; i < N; i++) {
        // Each position x_i in [-1e6, 1e6]
        string name = "x_" + to_string(i);
        inf.readInt(-1000000, 1000000, name.c_str());
        if (i + 1 < N) {
            // Exactly one space between positions
            inf.readSpace();
        } else {
            // End of the third line
            inf.readEoln();
        }
    }

    // No more data allowed
    inf.readEof();
    return 0;
}
