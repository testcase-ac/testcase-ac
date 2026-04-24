#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    // Read the street string S of length N, lowercase letters only
    string S = inf.readLine("[a-z]+", "S");
    ensuref((int)S.length() == N,
            "Length of S is %d but N is %d", (int)S.length(), N);

    // Read M
    int M = inf.readInt(1, 5000, "M");
    inf.readEoln();

    // Read each bundle tile, must be lowercase and length in [1,5000]
    for (int i = 0; i < M; i++) {
        string T = inf.readLine("[a-z]+", "tile");
        int len = (int)T.length();
        ensuref(1 <= len && len <= 5000,
                "Length of tile %d is %d but must be in [1,5000]", i+1, len);
    }

    inf.readEof();
    return 0;
}
