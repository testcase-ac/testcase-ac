#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Board size N: 2 ≤ N ≤ 100
    int N = inf.readInt(2, 100, "N");
    inf.readEoln();

    // Number of apples K: 0 ≤ K ≤ 100
    int K = inf.readInt(0, 100, "K");
    inf.readEoln();

    // Apple positions
    set<pair<int,int>> apples;
    for (int i = 0; i < K; i++) {
        int r = inf.readInt(1, N, "apple_row");
        inf.readSpace();
        int c = inf.readInt(1, N, "apple_col");
        inf.readEoln();

        // No apple at starting cell (1,1)
        ensuref(!(r == 1 && c == 1),
                "Apple at starting cell (1,1) at index %d", i);
        // All apple positions must be distinct
        pair<int,int> p = {r, c};
        ensuref(!apples.count(p),
                "Duplicate apple position at index %d: (%d,%d)", i, r, c);
        apples.insert(p);
    }

    // Number of direction changes L: 1 ≤ L ≤ 100
    int L = inf.readInt(1, 100, "L");
    inf.readEoln();

    // Direction change instructions
    int lastX = 0;
    for (int i = 0; i < L; i++) {
        // Time X: positive integer ≤ 10000
        int X = inf.readInt(1, 10000, "X");
        inf.readSpace();
        // Direction C: 'L' or 'D'
        string C = inf.readToken("[LD]", "C");
        inf.readEoln();

        // Times must be strictly increasing
        ensuref(X > lastX,
                "Direction change times not increasing at index %d: %d ≤ %d",
                i, X, lastX);
        lastX = X;
    }

    inf.readEof();
    return 0;
}
