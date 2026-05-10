#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N O S E
    int N = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int O = inf.readInt(1, 1000, "O");
    inf.readSpace();
    int S = inf.readInt(1, N, "S");
    inf.readSpace();
    int E = inf.readInt(1, N, "E");
    inf.readEoln();

    // Second line: M
    int M = inf.readInt(0, 10000, "M");
    inf.readEoln();

    // Next M lines: s_i e_i
    set<pair<int,int>> roads;
    for (int i = 0; i < M; ++i) {
        int s = inf.readInt(1, N, "s_i");
        inf.readSpace();
        int e = inf.readInt(1, N, "e_i");
        inf.readEoln();

        ensuref(s != e, "Road %d is a loop: (%d, %d)", i+1, s, e);
        int a = min(s, e), b = max(s, e);
        ensuref(!roads.count({a, b}), "Duplicate road at index %d: (%d, %d)", i+1, s, e);
        roads.insert({a, b});
    }

    // Next line: P
    int P = inf.readInt(0, 10000, "P");
    inf.readEoln();

    // Next P lines: w_i x_i
    set<pair<int,int>> wormholes;
    for (int i = 0; i < P; ++i) {
        int w = inf.readInt(1, O-1, "w_i");
        inf.readSpace();
        int x = inf.readInt(1, N, "x_i");
        inf.readEoln();

        ensuref(!wormholes.count({w, x}), "Duplicate wormhole at index %d: (w=%d, x=%d)", i+1, w, x);
        wormholes.insert({w, x});
    }

    // Next line: Q
    int Q = inf.readInt(1, 10000, "Q");
    inf.readEoln();

    // Next Q lines: a_i b_i
    for (int i = 0; i < Q; ++i) {
        int a = inf.readInt(0, 100, "a_i");
        inf.readSpace();
        int b = inf.readInt(0, 100, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
