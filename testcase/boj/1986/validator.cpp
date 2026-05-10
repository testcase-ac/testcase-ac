#include "testlib.h"
#include <vector>
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, m
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    // Helper to check if (r, c) is in bounds
    auto in_bounds = [&](int r, int c) {
        return 1 <= r && r <= n && 1 <= c && c <= m;
    };

    // To check for unique piece positions
    set<pair<int, int>> used;

    // Read Queen positions
    int q = inf.readInt(0, 100, "q");
    vector<pair<int, int>> queens;
    if (q > 0) inf.readSpace();
    for (int i = 0; i < q; ++i) {
        int r = inf.readInt(1, n, "queen_r");
        inf.readSpace();
        int c = inf.readInt(1, m, "queen_c");
        if (i + 1 < q) inf.readSpace();
        else inf.readEoln();
        ensuref(in_bounds(r, c), "Queen %d position (%d, %d) out of bounds", i+1, r, c);
        ensuref(!used.count({r, c}), "Duplicate piece at (%d, %d)", r, c);
        used.insert({r, c});
        queens.emplace_back(r, c);
    }
    if (q == 0) inf.readEoln();

    // Read Knight positions
    int k = inf.readInt(0, 100, "k");
    vector<pair<int, int>> knights;
    if (k > 0) inf.readSpace();
    for (int i = 0; i < k; ++i) {
        int r = inf.readInt(1, n, "knight_r");
        inf.readSpace();
        int c = inf.readInt(1, m, "knight_c");
        if (i + 1 < k) inf.readSpace();
        else inf.readEoln();
        ensuref(in_bounds(r, c), "Knight %d position (%d, %d) out of bounds", i+1, r, c);
        ensuref(!used.count({r, c}), "Duplicate piece at (%d, %d)", r, c);
        used.insert({r, c});
        knights.emplace_back(r, c);
    }
    if (k == 0) inf.readEoln();

    // Read Pawn positions
    int p = inf.readInt(0, 100, "p");
    vector<pair<int, int>> pawns;
    if (p > 0) inf.readSpace();
    for (int i = 0; i < p; ++i) {
        int r = inf.readInt(1, n, "pawn_r");
        inf.readSpace();
        int c = inf.readInt(1, m, "pawn_c");
        if (i + 1 < p) inf.readSpace();
        else inf.readEoln();
        ensuref(in_bounds(r, c), "Pawn %d position (%d, %d) out of bounds", i+1, r, c);
        ensuref(!used.count({r, c}), "Duplicate piece at (%d, %d)", r, c);
        used.insert({r, c});
        pawns.emplace_back(r, c);
    }
    if (p == 0) inf.readEoln();

    inf.readEof();
}
