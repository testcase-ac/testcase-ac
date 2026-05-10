#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of integers
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        // Each number: integer with |value| <= 1,000,000
        inf.readInt(-1000000, 1000000, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
