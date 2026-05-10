#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        int A = inf.readInt(0, 1000, "A");
        inf.readSpace();
        int B = inf.readInt(0, 1000, "B");
        inf.readEoln();
        // No further constraints per line
    }

    inf.readEof();
}
