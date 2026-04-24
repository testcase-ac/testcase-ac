#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of students
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    // Each student i (1-indexed) draws a number ai in [0, i-1]
    for (int i = 1; i <= n; i++) {
        // name the variable for clearer errors
        string name = "a_" + to_string(i);
        int ai = inf.readInt(0, i - 1, name.c_str());
        if (i < n)
            inf.readSpace();
        else
            inf.readEoln();
    }

    inf.readEof();
    return 0;
}
