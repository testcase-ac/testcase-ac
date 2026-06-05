#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "m");
    inf.readEoln();

    set<string> members;
    for (int i = 0; i < m; ++i) {
        string name = inf.readToken("[A-Z]{1,100}", "member_name");
        inf.readEoln();

        ensuref(members.insert(name).second,
                "duplicate member name at index %d: %s", i + 1, name.c_str());
    }

    for (int i = 0; i < n; ++i) {
        int k = inf.readInt(1, m, "k");
        set<string> liked;
        for (int j = 0; j < k; ++j) {
            inf.readSpace();
            string name = inf.readToken("[A-Z]{1,100}", "liked_member_name");

            ensuref(members.count(name) == 1,
                    "unknown liked member name for friend %d: %s", i + 1, name.c_str());
            ensuref(liked.insert(name).second,
                    "duplicate liked member name for friend %d: %s", i + 1, name.c_str());
        }
        inf.readEoln();
    }

    inf.readEof();
}
