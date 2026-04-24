#include "testlib.h"
#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 500000, "M");
    inf.readEoln();

    // Read the list of people who haven't been heard of (first list)
    set<string> heard_not;
    for (int i = 0; i < N; ++i) {
        // Name: lowercase letters only, length 1 to 20
        string name = inf.readToken("[a-z]{1,20}", "name1");
        inf.readEoln();
        auto res = heard_not.insert(name);
        ensuref(res.second,
                "Duplicate name in first list at line %d: %s",
                i + 2, name.c_str());
    }

    // Read the list of people who haven't been seen (second list)
    set<string> seen_not;
    for (int i = 0; i < M; ++i) {
        string name = inf.readToken("[a-z]{1,20}", "name2");
        inf.readEoln();
        auto res = seen_not.insert(name);
        ensuref(res.second,
                "Duplicate name in second list at line %d: %s",
                N + 2 + i, name.c_str());
    }

    inf.readEof();
    return 0;
}
