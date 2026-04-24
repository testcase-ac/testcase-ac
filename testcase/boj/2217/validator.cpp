#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of ropes
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read each rope's capacity
    for (int i = 0; i < N; i++) {
        inf.readInt(1, 10000, "w_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
