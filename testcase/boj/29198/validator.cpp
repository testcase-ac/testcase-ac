#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 300, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300, "M");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Read N strings of length M, uppercase letters
    for (int i = 1; i <= N; i++) {
        string s = inf.readToken("[A-Z]+", "S_i");
        ensuref((int)s.length() == M,
                "Length of S_%d is %d, but expected %d", i, (int)s.length(), M);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
