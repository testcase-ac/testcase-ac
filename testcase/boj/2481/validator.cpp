#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(2, 30, "k");
    inf.readEoln();

    set<string> codes;
    for (int i = 1; i <= n; ++i) {
        string code = inf.readToken("[01]{2,30}", "w_i");
        inf.readEoln();
        ensuref((int)code.size() == k, "code %d has length %d, expected %d", i, (int)code.size(), k);
        ensuref(codes.insert(code).second, "duplicate code at index %d: %s", i, code.c_str());
    }

    int m = inf.readInt(2, 50, "m");
    inf.readEoln();

    set<int> queries;
    for (int i = 1; i <= m; ++i) {
        int j = inf.readInt(2, n, "j");
        inf.readEoln();
        ensuref(queries.insert(j).second, "duplicate query target at index %d: %d", i, j);
    }

    inf.readEof();
}
