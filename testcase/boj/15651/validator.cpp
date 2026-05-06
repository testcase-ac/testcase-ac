#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M with the constraint 1 ≤ M ≤ N ≤ 7
    int N = inf.readInt(1, 7, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readEoln();

    inf.readEof();
    return 0;
}
