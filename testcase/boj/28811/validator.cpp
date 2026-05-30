#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int Q_MAX = 1000000;
    const int N_MAX = 1000000;

    int q = inf.readInt(1, Q_MAX, "q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        inf.readInt(1, N_MAX, "n_i");
        inf.readEoln();
    }

    inf.readEof();
}
