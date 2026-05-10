#include "testlib.h"
#include <vector>
#include <string>
#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and K
    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int K = inf.readInt(4, 1000, "K");
    inf.readEoln();

    vector<int> M(N);
    for (int i = 0; i < N; ++i) {
        // 2. Read M_i
        M[i] = inf.readInt(10, 1000, "M_i");
        inf.readEoln();

        // 3. Read program code line
        vector<int> code = inf.readInts(M[i], 1, 10000, "program_code");
        inf.readEoln();
    }

    inf.readEof();
}
