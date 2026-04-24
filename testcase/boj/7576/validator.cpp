#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M and N
    int M = inf.readInt(2, 1000, "M");
    inf.readSpace();
    int N = inf.readInt(2, 1000, "N");
    inf.readEoln();

    // Read the grid
    // Values must be -1 (empty), 0 (unripe), or 1 (ripe)
    long long tomato_count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (j > 0)
                inf.readSpace();
            int v = inf.readInt(-1, 1, "grid");
            if (v == 0 || v == 1)
                tomato_count++;
        }
        inf.readEoln();
    }

    // There must be at least one tomato (value 0 or 1)
    ensuref(tomato_count > 0,
            "No tomatoes in the warehouse: found only -1 entries");

    inf.readEof();
    return 0;
}
