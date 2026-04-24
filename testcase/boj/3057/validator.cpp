#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C
    int R = inf.readInt(1, 300, "R");
    inf.readSpace();
    int C = inf.readInt(1, 300, "C");
    inf.readEoln();

    // Read the R rows, each exactly C characters of '0' or '1'
    for (int i = 0; i < R; i++) {
        string row = inf.readLine("[01]+", "row");
        ensuref((int)row.size() == C,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), C);
    }

    inf.readEof();
    return 0;
}
