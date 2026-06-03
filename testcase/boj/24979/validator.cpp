#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[COW]{1,200000}", "s");
    inf.readEoln();

    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    int n = static_cast<int>(s.size());
    for (int i = 1; i <= q; ++i) {
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        int r = inf.readInt(l, n, "r");
        inf.readEoln();
    }

    inf.readEof();
}
