#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 300000, "K");
    inf.readEoln();

    // Read N jewels: weight M_i and value V_i
    for (int i = 0; i < N; i++) {
        int M_i = inf.readInt(0, 1000000, "M_i");
        inf.readSpace();
        int V_i = inf.readInt(0, 1000000, "V_i");
        inf.readEoln();
    }

    // Read K bags: capacity C_i
    for (int i = 0; i < K; i++) {
        int C_i = inf.readInt(1, 100000000, "C_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
