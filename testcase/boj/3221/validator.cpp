#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int l = inf.readInt(2, 200000, "L");
    inf.readSpace();
    int t = inf.readInt(1, 1000000, "T");
    inf.readEoln();

    int n = inf.readInt(1, 70000, "N");
    inf.readEoln();
    ensuref(n < l, "N must be less than L: N=%d, L=%d", n, l);

    int previous = -1;
    for (int i = 1; i <= n; ++i) {
        // CHECK: the statement omits explicit position bounds; N < L suggests
        // integer starting positions are the interior millimeter marks.
        int position = inf.readInt(1, l - 1, "position");
        inf.readSpace();

        // CHECK: the Korean statement and official samples use D for right,
        // while the English variant says R. Follow the primary statement.
        string direction = inf.readToken("L|D", "direction");
        inf.readEoln();

        ensuref(previous < position,
                "positions must be strictly increasing by ant number: previous=%d, current=%d at ant %d",
                previous, position, i);
        previous = position;
    }

    inf.readEof();
}
