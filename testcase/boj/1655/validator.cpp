#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of integers
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read each integer and ensure bounds
    for (int i = 0; i < N; i++) {
        inf.readInt(-10000, 10000, "a_i");
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
