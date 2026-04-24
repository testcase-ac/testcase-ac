#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 10, "N");
    inf.readEoln();

    // Read the memory counts for heights 1..N
    for (int i = 1; i <= N; i++) {
        // For the i-th person (height = i), the value must be in [0, N-i]
        char name[20];
        sprintf(name, "a_%d", i);
        int x = inf.readInt(0, N - i, name);
        if (i < N) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    // No extra data
    inf.readEof();
    return 0;
}
