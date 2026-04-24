#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 20, "M");
    inf.readEoln();

    // Read each box
    for (int i = 1; i <= N; i++) {
        // Number of toy types in box i
        int Ki = inf.readInt(0, M, "K_i");
        int mask = 0;
        // Read Ki toy types
        for (int j = 0; j < Ki; j++) {
            inf.readSpace();
            int t = inf.readInt(1, M, "toy_type");
            // Check for duplicates in the same box
            ensuref(!(mask & (1 << (t - 1))),
                    "Duplicate toy type %d in box %d", t, i);
            mask |= 1 << (t - 1);
        }
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
