#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of sticks
    int N = inf.readInt(2, 100000, "N");
    inf.readEoln();

    // Read each height on its own line
    for (int i = 0; i < N; i++) {
        char name[16];
        sprintf(name, "h_%d", i+1);
        inf.readInt(1, 100000, name);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
