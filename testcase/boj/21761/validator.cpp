#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and K
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // 2. Read A_0, B_0, C_0, D_0
    int A0 = inf.readInt(1, 1000000, "A_0");
    inf.readSpace();
    int B0 = inf.readInt(1, 1000000, "B_0");
    inf.readSpace();
    int C0 = inf.readInt(1, 1000000, "C_0");
    inf.readSpace();
    int D0 = inf.readInt(1, 1000000, "D_0");
    inf.readEoln();

    // 3. Read N cards
    for (int i = 0; i < N; ++i) {
        std::string Ti = inf.readToken("[A-D]", "T_i");
        inf.readSpace();
        int Ui = inf.readInt(1, 1000000, "U_i");
        inf.readEoln();
    }

    inf.readEof();
}
