#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read S
    string S = inf.readToken("[a-z]{1,100000}", "S");
    ensuref((int)S.size() == N, "Length of S (%d) does not match N (%d)", (int)S.size(), N);
    inf.readEoln();

    inf.readEof();
}
