#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int S = inf.readInt(0, 100, "S");
    inf.readSpace();
    int K = inf.readInt(0, 100, "K");
    inf.readSpace();
    int H = inf.readInt(0, 100, "H");
    inf.readEoln();

    ensuref(S != K, "S and K must be distinct, but both are %d", S);
    ensuref(S != H, "S and H must be distinct, but both are %d", S);
    ensuref(K != H, "K and H must be distinct, but both are %d", K);

    inf.readEof();
    return 0;
}
