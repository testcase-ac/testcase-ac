#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readSpace();
    int k = inf.readInt(1, 100, "K");
    inf.readEoln();

    vector<bool> reachable(m + 1, false);
    reachable[0] = true;

    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(1, 100, "X");
        inf.readSpace();
        int y = inf.readInt(1, 100, "Y");
        inf.readEoln();

        (void)x;
        for (int damage = y; damage <= m; ++damage) {
            reachable[damage] = reachable[damage] || reachable[damage - y];
        }
    }

    ensuref(reachable[m], "no skill combination can make exact health %d", m);

    inf.readEof();
}
