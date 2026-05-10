#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int maxM = (N + 1) / 2;
    int M = inf.readInt(1, maxM, "M");
    inf.readEoln();

    // Read the array elements
    for (int i = 0; i < N; i++) {
        inf.readInt(-32768, 32767, "a_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
