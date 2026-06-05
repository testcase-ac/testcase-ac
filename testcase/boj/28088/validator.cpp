#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200, "N");
    inf.readSpace();
    int m = inf.readInt(1, n, "M");
    inf.readSpace();
    inf.readInt(0, 1000000, "K");
    inf.readEoln();

    set<int> initial;
    for (int i = 0; i < m; ++i) {
        int person = inf.readInt(0, n - 1, "person");
        inf.readEoln();
        ensuref(initial.insert(person).second,
                "duplicate initial greeter at line %d: %d", i + 2, person);
    }

    inf.readEof();
}
