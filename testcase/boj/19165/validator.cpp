#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    // Read string S of length N, consisting only of 'A' and 'B'
    string S = inf.readToken("[AB]+", "S");
    ensuref((int)S.size() == N, "Length of S must be %d, but got %d", N, (int)S.size());
    inf.readEoln();

    // Read Q commands
    bool hasType2 = false;
    for (int i = 0; i < Q; i++) {
        // Command type (1 or 2)
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        // Common L and R
        int L = inf.readInt(1, N, "L");
        inf.readSpace();
        int R = inf.readInt(L, N, "R"); // ensure L <= R
        if (type == 1) {
            // Type 1: exactly "1 L R"
            inf.readEoln();
        } else {
            // Type 2: "2 L R A B"
            hasType2 = true;
            inf.readSpace();
            long long A = inf.readLong(0LL, 1000000000LL, "A");
            inf.readSpace();
            long long B = inf.readLong(0LL, 1000000000LL, "B");
            inf.readEoln();
        }
    }

    // There must be at least one type-2 command
    ensuref(hasType2, "There must be at least one command of type 2");

    inf.readEof();
    return 0;
}
