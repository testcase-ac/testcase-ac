#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of sharks N, 1 <= N <= 50
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // For each shark, read three positive integers <= 2e9
    for (int i = 0; i < N; i++) {
        // Size
        inf.readLong(1LL, 2000000000LL, "size");
        inf.readSpace();
        // Speed
        inf.readLong(1LL, 2000000000LL, "speed");
        inf.readSpace();
        // Intelligence
        inf.readLong(1LL, 2000000000LL, "intelligence");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
