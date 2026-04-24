#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of students N and show duration C
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int C = inf.readInt(1, 2000000, "C");
    inf.readEoln();

    // Read each student's period
    for (int i = 0; i < N; i++) {
        inf.readInt(1, C, "period");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
