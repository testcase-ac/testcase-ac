#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int R = inf.readInt(2, 3000, "R");
    inf.readSpace();
    int C = inf.readInt(2, 3000, "C");
    inf.readEoln();

    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();
    ensuref(static_cast<long long>(N) < static_cast<long long>(R) * C,
            "at least one cell must be empty: R=%d C=%d N=%d", R, C, N);

    set<pair<int, int>> occupied;
    for (int i = 0; i < N; ++i) {
        int A = inf.readInt(1, R, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, C, "B_i");
        inf.readEoln();

        ensuref(occupied.insert({A, B}).second,
                "duplicate occupied cell at index %d: (%d, %d)", i + 1, A, B);
    }

    inf.readEof();
    return 0;
}
