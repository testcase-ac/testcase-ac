#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10, "M");
    inf.readEoln();

    set<string> words;
    for (int i = 0; i < n; ++i) {
        string q = inf.readToken("[A-Z]{1,10}", "Q_i");
        inf.readSpace();
        inf.readToken("[A-Z]{1,10}", "A_i");
        inf.readEoln();

        ensuref(words.insert(q).second, "duplicate Q_i at index %d: %s", i + 1, q.c_str());
    }

    for (int i = 0; i < m; ++i) {
        inf.readToken("[A-Z]{1,100}", "S_i");
        inf.readEoln();
    }

    inf.readEof();
}
