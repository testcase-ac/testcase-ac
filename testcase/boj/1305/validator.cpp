#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int L = inf.readInt(1, 1000000, "L");
    inf.readEoln();

    string S = inf.readToken("[a-z]{1,1000000}", "S");
    ensuref((int)S.size() == L, "S length must be L=%d, got %d", L, (int)S.size());
    inf.readEoln();

    inf.readEof();
}
