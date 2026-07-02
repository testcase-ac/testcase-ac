#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const string namePattern = "[A-Za-z]{1,20}";
    set<string> members;

    int n = inf.readInt(1, 50000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string name = inf.readToken(namePattern, "s_i");
        inf.readSpace();
        inf.readInt(0, 100000, "a_i");
        inf.readEoln();

        ensuref(members.insert(name).second,
                "duplicate initial member name at index %d: %s", i + 1,
                name.c_str());
    }

    int m = inf.readInt(1, 20000, "M");
    inf.readEoln();

    for (int j = 0; j < m; ++j) {
        string eventType = inf.readToken("[+-]", "event_type");
        inf.readSpace();
        string name = inf.readToken(namePattern, "t_j");

        if (eventType == "+") {
            inf.readSpace();
            inf.readInt(0, 100000, "b_j");
            inf.readEoln();

            ensuref(!members.count(name),
                    "incoming member already belongs to ACM at event %d: %s",
                    j + 1, name.c_str());
            members.insert(name);
        } else {
            inf.readEoln();

            ensuref(members.count(name),
                    "outgoing member does not belong to ACM at event %d: %s",
                    j + 1, name.c_str());
            members.erase(name);
        }
    }

    inf.readEof();
}
