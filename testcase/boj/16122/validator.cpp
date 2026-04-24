#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M according to constraints
    int N = inf.readInt(0, 300000, "N");
    inf.readSpace();
    int M = inf.readInt(-300000, 300000, "M");
    inf.readEoln();

    // No further global constraints implied by the problem statement
    inf.readEof();
    return 0;
}
