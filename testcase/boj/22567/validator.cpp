#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

namespace {

void readBoard(int n, const char* name) {
    set<int> seen;
    for (int i = 0; i < n; ++i) {
        vector<int> row = inf.readInts(n, 1, 1000000, name);
        inf.readEoln();
        for (int x : row) {
            ensuref(seen.insert(x).second, "%s contains duplicate value %d", name, x);
        }
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    inf.readInt(1, 13, "u");
    inf.readSpace();
    inf.readInt(1, 13, "v");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    readBoard(n, "usagi_board");
    readBoard(n, "neko_board");

    set<int> drawn;
    for (int i = 0; i < m; ++i) {
        int card = inf.readInt(1, 1000000, "drawn_card");
        inf.readEoln();
        ensuref(drawn.insert(card).second, "drawn cards contain duplicate value %d", card);
    }

    inf.readEof();
}
