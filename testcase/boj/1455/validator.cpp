#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        string row = inf.readToken("[01]{1,100}", "row");
        ensuref((int)row.size() == M,
                "row %d has length %d, expected %d", i + 1, (int)row.size(), M);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
