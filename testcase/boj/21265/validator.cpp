#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case, one line with 6 integers:
    // N, M (1..200), K (1..100), R (1..N), C (1..M), V (1..K)

    int N = inf.readInt(1, 200, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200, "M");
    inf.readSpace();
    int K = inf.readInt(1, 100, "K");
    inf.readSpace();
    int R = inf.readInt(1, N, "R");
    inf.readSpace();
    int C = inf.readInt(1, M, "C");
    inf.readSpace();
    int V = inf.readInt(1, K, "V");
    inf.readEoln();

    // All cross-constraints are already ensured by using N, M, K as bounds:
    // 1 <= R <= N, 1 <= C <= M, 1 <= V <= K.

    inf.readEof();
}
