#include "testlib.h"

#include <array>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    array<int, 6> a{};
    array<int, 6> b{};

    for (int i = 0; i < 6; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        a[i] = inf.readInt(-1000, 1000, "a_coord");
    }
    inf.readEoln();

    for (int i = 0; i < 6; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        b[i] = inf.readInt(-1000, 1000, "b_coord");
    }
    inf.readEoln();

    ensuref(array<int, 3>{a[0], a[1], a[2]} != array<int, 3>{b[0], b[1], b[2]},
            "robots must start in different places");
    ensuref(array<int, 3>{a[3], a[4], a[5]} != array<int, 3>{b[3], b[4], b[5]},
            "robots must end in different places");

    inf.readEof();
}
