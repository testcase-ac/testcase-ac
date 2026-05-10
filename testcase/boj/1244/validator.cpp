#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of switches
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    // Initial switch states: exactly n tokens, each 0 or 1, separated by one space
    for (int i = 0; i < n; i++) {
        inf.readInt(0, 1, "state");
        if (i + 1 < n)
            inf.readSpace();
        else
            inf.readEoln();
    }

    // Number of students
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    // Each student's gender and number
    for (int i = 0; i < m; i++) {
        inf.readInt(1, 2, "gender");  // 1 = male, 2 = female
        inf.readSpace();
        inf.readInt(1, n, "k");       // the number each student receives
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
