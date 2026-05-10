#include "testlib.h"
#include <vector>
#include <set>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 20000, "M");
    inf.readEoln();

    // To check for valid room coordinates and duplicate switches
    set<tuple<int,int,int,int>> switches;

    for (int i = 0; i < M; ++i) {
        int x = inf.readInt(1, N, "x");
        inf.readSpace();
        int y = inf.readInt(1, N, "y");
        inf.readSpace();
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(1, N, "b");
        inf.readEoln();

        // Check for duplicate switches
        auto key = make_tuple(x, y, a, b);
        ensuref(switches.count(key) == 0, 
            "Duplicate switch at line %d: (%d,%d)->(%d,%d)", i+2, x, y, a, b);
        switches.insert(key);
    }

    inf.readEof();
}
