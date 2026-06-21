#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "n");
    inf.readEoln();

    string s = inf.readToken("[OX]{2,200000}", "s");
    ensuref((int)s.size() == n, "s length must be n: expected %d, got %d", n,
            (int)s.size());
    inf.readEoln();

    int beads = 0;
    for (char c : s) {
        beads += c == 'O';
    }
    ensuref(beads > 0, "initial barrel must contain at least one bead");

    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int k = inf.readInt(1, n, "k");
        inf.readEoln();

        char& cell = s[k - 1];
        if (cell == 'O') {
            cell = 'X';
            --beads;
        } else {
            cell = 'O';
            ++beads;
        }
        ensuref(beads > 0, "barrel has zero beads after action %d", i);
    }

    inf.readEof();
}
