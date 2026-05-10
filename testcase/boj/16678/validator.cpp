#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read N lines, each with a_i
    for (int i = 1; i <= N; ++i) {
        int a_i = inf.readInt(1, 100000, "a_i");
        inf.readEoln();
    }

    inf.readEof();
}
