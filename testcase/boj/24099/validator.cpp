#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int l = inf.readInt(1, 300000, "L");
    inf.readEoln();

    string document = inf.readToken("[A-Z]{1,300000}", "document");
    ensuref((int)document.size() == l, "document length %d does not match L %d",
            (int)document.size(), l);
    inf.readEoln();

    int m = inf.readInt(0, 26 * 26, "M");
    inf.readEoln();

    set<pair<char, char>> rules;
    for (int i = 1; i <= m; ++i) {
        string a = inf.readToken("[A-Z]", "A_i");
        inf.readSpace();
        string b = inf.readToken("[A-Z]", "B_i");
        inf.readEoln();

        pair<char, char> rule = {a[0], b[0]};
        ensuref(rules.insert(rule).second, "duplicate rule at index %d: %c %c",
                i, rule.first, rule.second);
    }

    inf.readEof();
}
