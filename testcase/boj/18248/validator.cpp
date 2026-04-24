#include "testlib.h"
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Read the N lines of hearing information
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            char name[50];
            std::sprintf(name, "a_%d_%d", i, j);
            inf.readInt(0, 1, name);
            if (j < M) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
