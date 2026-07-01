#include "testlib.h"

#include <array>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string v = inf.readToken("[a-z]{1,26}", "v");
    inf.readEoln();

    array<bool, 26> allowed{};
    for (int i = 0; i < (int)v.size(); ++i) {
        int c = v[i] - 'a';
        ensuref(!allowed[c], "duplicate character in v: %c", v[i]);
        if (i > 0) {
            ensuref(v[i - 1] < v[i], "v is not in lexicographical order");
        }
        allowed[c] = true;
    }

    string s = inf.readToken("[a-z]{1,1000000}", "s");
    inf.readEoln();
    for (int i = 0; i < (int)s.size(); ++i) {
        ensuref(allowed[s[i] - 'a'], "s[%d] is not in v: %c", i + 1, s[i]);
    }

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    long long totalQueryLength = 0;
    for (int i = 0; i < n; ++i) {
        string q = inf.readToken("[a-z]{1,1000000}", "q");
        inf.readEoln();

        totalQueryLength += (long long)q.size();
        ensuref(totalQueryLength <= 1000000LL,
                "sum of query lengths exceeds 1000000 at query %d", i + 1);

        for (int j = 0; j < (int)q.size(); ++j) {
            ensuref(allowed[q[j] - 'a'], "q[%d][%d] is not in v: %c",
                    i + 1, j + 1, q[j]);
        }
    }

    inf.readEof();
}
