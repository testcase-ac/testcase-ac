#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 200, "T");
    inf.readSpace();
    int A = inf.readInt(1, 4000, "A");
    inf.readSpace();
    int S = inf.readInt(1, A, "S");
    inf.readSpace();
    int B = inf.readInt(S, A, "B");
    inf.readEoln();

    vector<int> values = inf.readInts(A, 1, T, "value");
    (void)values;
    inf.readEoln();

    inf.readEof();
}
