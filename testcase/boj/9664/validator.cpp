#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of daughters N
    int N = inf.readInt(2, 15, "N");
    inf.readEoln();

    // Read number of remaining medallions O
    // It must satisfy N <= O <= 100
    int O = inf.readInt((long long)N, 100, "O");
    inf.readEoln();

    inf.readEof();
    return 0;
}
