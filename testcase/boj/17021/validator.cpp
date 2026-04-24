#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, M, K
    int N = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readSpace();
    int K = inf.readInt(1, 5000, "K");
    inf.readEoln();

    // Next N lines: s_i and c_i
    for (int i = 0; i < N; i++) {
        int s = inf.readInt(1, K, "s_i");
        inf.readSpace();
        int c = inf.readInt(1, N, "c_i");
        inf.readEoln();
    }

    // Next M lines: single uppercase letter e_i
    for (int i = 0; i < M; i++) {
        inf.readToken("[A-Z]", "e_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
