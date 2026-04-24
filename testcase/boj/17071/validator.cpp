#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read Subin's position N and sibling's position K
    int N = inf.readInt(0, 500000, "N");
    inf.readSpace();
    int K = inf.readInt(0, 500000, "K");
    inf.readEoln();

    // No further global constraints to check from problem statement

    inf.readEof();
    return 0;
}
