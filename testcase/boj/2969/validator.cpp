#include "testlib.h"
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1500, "N");
    inf.readEoln();

    // Read starting position R, C
    int R = inf.readInt(1, N, "R");
    inf.readSpace();
    int C = inf.readInt(1, N, "C");
    inf.readEoln();

    // Read the flower petals grid
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            // Petal count: 0 <= a[i][j] <= 1e6
            // (No negative petals; assume 0 is allowed since lower bound is not specified)
            inf.readInt(0, 1000000, ("a_" + to_string(i) + "_" + to_string(j)).c_str());
            if (j < N) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
