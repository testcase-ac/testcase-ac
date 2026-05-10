#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(3, 8, "N");
    inf.readSpace();
    int M = inf.readInt(3, 8, "M");
    inf.readEoln();

    int zero_count = 0;
    int two_count = 0;

    // Read grid
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char name_buf[30];
            snprintf(name_buf, sizeof(name_buf), "grid_%d_%d", i+1, j+1);
            int v = inf.readInt(0, 2, name_buf);
            if (j < M-1) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
            if (v == 0) zero_count++;
            if (v == 2) two_count++;
        }
    }

    // Validate global counts
    ensuref(zero_count >= 3,
            "The number of empty cells must be at least 3, found %d", zero_count);
    ensuref(two_count >= 2 && two_count <= 10,
            "The number of virus cells must be between 2 and 10, found %d", two_count);

    inf.readEof();
    return 0;
}
