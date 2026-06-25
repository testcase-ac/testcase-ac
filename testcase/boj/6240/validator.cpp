#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 26, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "M");
    inf.readEoln();

    string s = inf.readToken("[a-z]{1,2000}", "initial_id");
    ensuref((int)s.size() == m, "initial_id length is %d, expected M=%d",
            (int)s.size(), m);
    inf.readEoln();

    set<char> alphabet;
    for (int i = 0; i < n; ++i) {
        string ch = inf.readToken("[a-z]", "alphabet_char");
        inf.readSpace();
        int insertCost = inf.readInt(0, 10000, "insert_cost");
        inf.readSpace();
        int deleteCost = inf.readInt(0, 10000, "delete_cost");
        inf.readEoln();

        ensuref(alphabet.insert(ch[0]).second,
                "duplicate alphabet character '%c' at row %d", ch[0], i + 1);
        (void)insertCost;
        (void)deleteCost;
    }

    for (int i = 0; i < m; ++i) {
        ensuref(alphabet.count(s[i]) != 0,
                "initial_id character '%c' at position %d is not in alphabet",
                s[i], i + 1);
    }

    inf.readEof();
}
