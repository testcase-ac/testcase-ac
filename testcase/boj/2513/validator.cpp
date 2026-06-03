#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 30000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 2000, "K");
    inf.readSpace();
    int s = inf.readInt(0, 100000, "S");
    inf.readEoln();

    set<int> coordinates;
    coordinates.insert(s);

    for (int i = 1; i <= n; ++i) {
        int position = inf.readInt(0, 100000, "position");
        inf.readSpace();
        inf.readInt(1, 2000, "students");
        inf.readEoln();

        ensuref(coordinates.insert(position).second,
                "coordinate at apartment %d is not distinct: %d", i, position);
    }

    inf.readEof();
}
