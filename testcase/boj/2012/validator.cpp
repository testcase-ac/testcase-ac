#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read N lines, each with a_i
    for (int i = 0; i < N; ++i) {
        int a_i = inf.readInt(1, 500000, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
