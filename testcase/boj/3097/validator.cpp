#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of segments N: must satisfy 1 < N ≤ 30
    int N = inf.readInt(2, 30, "N");
    inf.readEoln();

    // Each of the next N lines: two integers X, Y with -1000 ≤ X, Y ≤ 1000
    for (int i = 0; i < N; i++) {
        string xn = "X_" + to_string(i+1);
        string yn = "Y_" + to_string(i+1);
        inf.readInt(-1000, 1000, xn.c_str());
        inf.readSpace();
        inf.readInt(-1000, 1000, yn.c_str());
        inf.readEoln();
    }

    // No extra data after the N lines
    inf.readEof();
    return 0;
}
