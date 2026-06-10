#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    int breed_count[2] = {0, 0};
    set<int> seen_x;

    for (int i = 0; i < n; ++i) {
        int breed = inf.readInt(0, 1, "breed");
        inf.readSpace();
        int x = inf.readInt(0, 1000000000, "x");
        inf.readEoln();

        ++breed_count[breed];
        ensuref(seen_x.insert(x).second,
                "duplicate x-coordinate at cow %d: %d", i + 1, x);
    }

    ensuref(breed_count[0] >= 1, "at least one breed 0 cow must appear");
    ensuref(breed_count[1] >= 1, "at least one breed 1 cow must appear");

    inf.readEof();
}
