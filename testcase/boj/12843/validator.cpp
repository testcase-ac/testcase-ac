#include "testlib.h"
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();

    vector<char> department(n + 1);
    vector<bool> seenCourse(n + 1, false);
    for (int i = 0; i < n; ++i) {
        int course = inf.readInt(1, n, "course");
        inf.readSpace();
        string dept = inf.readToken("c|s", "department");
        inf.readEoln();

        ensuref(!seenCourse[course], "duplicate course number %d", course);
        seenCourse[course] = true;
        department[course] = dept[0];
    }

    set<pair<int, int>> relations;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(department[a] != department[b],
                "relation %d does not connect different departments: %d %d",
                i + 1, a, b);
        auto relation = minmax(a, b);
        ensuref(relations.insert(relation).second,
                "duplicate relation at index %d: %d %d", i + 1, a, b);
    }

    inf.readEof();
    return 0;
}
