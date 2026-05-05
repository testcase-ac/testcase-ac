#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read F, P, C, M
    int F = inf.readInt(1, 500, "F");
    inf.readSpace();
    int P = inf.readInt(1, 1000, "P");
    inf.readSpace();
    int C = inf.readInt(1, 100, "C");
    inf.readSpace();
    int M = inf.readInt(1, 70000, "M");
    inf.readEoln();

    // Read P edges
    // Validate only what the statement specifies: ranges and formatting
    for (int i = 0; i < P; ++i) {
        int F1 = inf.readInt(1, F, "F1");
        inf.readSpace();
        int F2 = inf.readInt(1, F, "F2");
        inf.readSpace();
        int T = inf.readInt(1, 70000, "T");
        inf.readEoln();
        (void)F1; (void)F2; (void)T;
    }

    // Read C cow locations
    for (int i = 1; i <= C; ++i) {
        int cow_field = inf.readInt(1, F, "cow_field");
        (void)cow_field;
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
