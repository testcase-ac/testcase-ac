#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There is exactly one test case: 6 lines, each with one integer [0,100].
    int A = inf.readInt(0, 100, "A");
    inf.readEoln();
    int B = inf.readInt(0, 100, "B");
    inf.readEoln();
    int C = inf.readInt(0, 100, "C");
    inf.readEoln();
    int D = inf.readInt(0, 100, "D");
    inf.readEoln();
    int E = inf.readInt(0, 100, "E");
    inf.readEoln();
    int F = inf.readInt(0, 100, "F");
    inf.readEoln();

    inf.readEof();
    return 0;
}
