#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 2000, "N");
    inf.readEoln();

    // 2. Read A
    string A = inf.readToken("[01]{1,2000}", "A");
    ensuref(int(A.size()) == N, "Length of A (%d) does not match N (%d)", int(A.size()), N);
    inf.readEoln();

    // 3. Read B
    string B = inf.readToken("[01]{1,2000}", "B");
    ensuref(int(B.size()) == N, "Length of B (%d) does not match N (%d)", int(B.size()), N);
    inf.readEoln();

    // 4. Read p1, p3, p5, p_pair
    int p1 = inf.readInt(1, 10000, "p_1");
    inf.readSpace();
    int p3 = inf.readInt(1, 10000, "p_3");
    inf.readSpace();
    int p5 = inf.readInt(1, 10000, "p_5");
    inf.readSpace();
    int p_pair = inf.readInt(1, 10000, "p_pair");
    inf.readEoln();

    inf.readEof();
}
