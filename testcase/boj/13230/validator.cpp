#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 200, "C");
    inf.readEoln();

    for (int tc = 1; tc <= c; ++tc) {
        setTestCase(tc);

        string s = inf.readToken("[01?]{1,100}", "S");
        inf.readEoln();
        string t = inf.readToken("[01]{1,100}", "T");
        inf.readEoln();

        ensuref(s.size() == t.size(),
                "S and T must have equal lengths, got %d and %d",
                int(s.size()), int(t.size()));
    }

    inf.readEof();
}
