#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, C
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readSpace();
    int C = inf.readInt(0, 50, "C");
    inf.readEoln();

    // Read C arcade positions
    vector<pair<int, int>> arcades;
    set<pair<int, int>> arcade_set;
    for (int i = 0; i < C; ++i) {
        int r = inf.readInt(1, N, "arcade_row");
        inf.readSpace();
        int c = inf.readInt(1, M, "arcade_col");
        inf.readEoln();
        pair<int, int> pos = make_pair(r, c);
        ensuref(!arcade_set.count(pos), "Arcade position duplicated at index %d: (%d, %d)", i+1, r, c);
        arcade_set.insert(pos);
        arcades.push_back(pos);
    }

    // No further input
    inf.readEof();
}
