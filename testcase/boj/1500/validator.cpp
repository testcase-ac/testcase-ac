#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int S = inf.readInt(1, 100, "S");
    inf.readSpace();
    int K = inf.readInt(1, 20, "K");
    inf.readEoln();

    ensuref(K <= S, "K must be at most S, but S = %d and K = %d", S, K);

    inf.readEof();
    return 0;
}
