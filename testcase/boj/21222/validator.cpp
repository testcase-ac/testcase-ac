#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    set<string> words;
    for (int i = 1; i <= m; ++i) {
        string x = inf.readToken("[a-z]{1,20}", "x_i");
        inf.readSpace();
        string y = inf.readToken("[a-z]{1,20}", "y_i");
        inf.readSpace();
        long long t = inf.readLong(1LL, 1000000000LL, "t_i");
        inf.readEoln();

        ensuref(x != y, "connection %d has equal words: %s", i, x.c_str());
        words.insert(x);
        words.insert(y);
    }

    ensuref((int)words.size() == n,
            "number of distinct words in connections is %d, expected n=%d",
            (int)words.size(), n);

    int q = inf.readInt(1, 1000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        string a = inf.readToken("[a-z]{1,20}", "a_i");
        inf.readSpace();
        string b = inf.readToken("[a-z]{1,20}", "b_i");
        inf.readEoln();

        ensuref(a != b, "query %d has equal words: %s", i, a.c_str());
        ensuref(words.count(a) != 0, "query %d uses unknown source word: %s",
                i, a.c_str());
        ensuref(words.count(b) != 0, "query %d uses unknown target word: %s",
                i, b.c_str());
    }

    inf.readEof();
}
