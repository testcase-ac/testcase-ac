#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;
    const int MAXM = 100000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readSpace();
    int M = inf.readInt(1, MAXM, "M");
    inf.readEoln();

    // Simulate trains to also validate any implied conditions if needed
    // N trains, 20 seats each, empty initially
    vector<unsigned int> train(N, 0); // use 20 bits

    for (int cmdIdx = 0; cmdIdx < M; ++cmdIdx) {
        int t = inf.readInt(1, 4, "command_type");
        if (t == 1 || t == 2) {
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            int x = inf.readInt(1, 20, "x");
            inf.readEoln();

            // simulate to ensure internal consistency
            unsigned int mask = 1u << (x - 1);
            if (t == 1) {
                // board passenger if not already
                train[i - 1] |= mask;
            } else {
                // remove passenger if exists
                train[i - 1] &= ~mask;
            }
        } else if (t == 3) {
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readEoln();

            // shift passengers back (to higher seat index)
            // seat 20 leaves
            train[i - 1] <<= 1;
            // clear bits beyond 20
            train[i - 1] &= (1u << 20) - 1;
        } else { // t == 4
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readEoln();

            // shift passengers forward (to lower seat index)
            // seat 1 leaves
            train[i - 1] >>= 1;
        }
    }

    inf.readEof();
}
