#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read N+1 integers a_i
    for (int i = 0; i <= N; i++) {
        inf.readInt(1, 100000, "a_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
