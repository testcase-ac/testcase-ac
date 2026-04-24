#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 1500, "N");
    inf.readEoln();

    // Read points and check constraints
    set<pair<int,int>> seen;
    for (int i = 0; i < N; i++) {
        int x = inf.readInt(-100000000, 100000000, "X_i");
        inf.readSpace();
        int y = inf.readInt(-100000000, 100000000, "Y_i");
        inf.readEoln();
        bool inserted = seen.insert(make_pair(x, y)).second;
        ensuref(inserted,
                "Duplicate point at index %d: (%d, %d)", 
                i, x, y);
    }

    inf.readEof();
    return 0;
}
