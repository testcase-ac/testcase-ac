#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of multi-taps
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // For each multi-tap, read its number of sockets
    for (int i = 0; i < N; i++) {
        int k = inf.readInt(1, 1000, "k_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
