#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 1000, "Q");
    inf.readEoln();

    set<string> a;
    set<string> b;
    bool hasFind = false;

    for (int i = 1; i <= q; ++i) {
        string op = inf.readToken("add|delete|find", "query_type");

        if (op == "find") {
            inf.readSpace();
            inf.readToken("[a-z]{1,1000}", "S");
            inf.readEoln();
            hasFind = true;
            continue;
        }

        inf.readSpace();
        string target = inf.readToken("A|B", "target_set");
        inf.readSpace();
        string s = inf.readToken("[a-z]{1,1000}", "S");
        inf.readEoln();

        set<string>& selected = (target == "A" ? a : b);
        if (op == "add") {
            ensuref(selected.insert(s).second,
                    "query %d adds an already existing string to set %s: %s",
                    i, target.c_str(), s.c_str());
        } else {
            ensuref(selected.erase(s) == 1,
                    "query %d deletes a missing string from set %s: %s",
                    i, target.c_str(), s.c_str());
        }
    }

    ensuref(hasFind, "at least one find query is required");
    inf.readEof();
}
