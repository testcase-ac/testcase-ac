#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[a-z]{1,100000}", "s");
    inf.readEoln();
    int q = inf.readInt(0, 100000, "q");
    inf.readEoln();

    for (int query = 1; query <= q; ++query) {
        setTestCase(query);
        int i = inf.readInt(1, static_cast<int>(s.size()), "i");
        inf.readSpace();
        string c = inf.readToken("[a-z]", "c");
        inf.readEoln();
        ensuref(s[i - 1] != c[0],
                "query %d does not change position %d", query, i);
        s[i - 1] = c[0];
    }

    inf.readEof();
}
