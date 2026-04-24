#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of machines
    int N = inf.readInt(3, 100000, "N");
    inf.readEoln();

    // Read M_i for each machine, one per line
    for (int i = 1; i <= N; i++) {
        inf.readInt(1, 10000, "M_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
