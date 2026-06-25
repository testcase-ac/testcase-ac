#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "n");
    inf.readEoln();

    set<string> uniquePokemon;
    for (int i = 0; i < n; ++i) {
        int r = inf.readInt(-100, 100, "r");
        inf.readSpace();
        int c = inf.readInt(-100, 100, "c");
        inf.readSpace();
        string p = inf.readToken("[a-zA-Z]{1,25}", "p");
        inf.readEoln();

        (void)r;
        (void)c;
        uniquePokemon.insert(p);
    }

    ensuref(uniquePokemon.size() <= 15,
            "number of unique Pokemon names is %d, expected at most 15",
            static_cast<int>(uniquePokemon.size()));

    inf.readEof();
    return 0;
}
