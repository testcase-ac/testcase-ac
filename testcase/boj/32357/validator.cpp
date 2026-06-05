#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 10000, "N");
    inf.readEoln();

    set<string> seen;
    for (int i = 0; i < n; ++i) {
        string s = inf.readToken("[a-z]{2,1000}", "s_i");
        inf.readEoln();

        ensuref(s.size() % 2 == 0, "s_%d has odd length %d", i + 1, int(s.size()));
        ensuref(seen.insert(s).second, "duplicate string at index %d: %s", i + 1, s.c_str());
    }

    inf.readEof();
}
