#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readToken("[a-r]{1,100000}", "s");
    inf.readEoln();
    string t = inf.readToken("[a-r]{1,100000}", "t");
    inf.readEoln();

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    set<string> seen_queries;
    for (int i = 0; i < q; ++i) {
        string query = inf.readToken("[a-r]{1,18}", "query");
        inf.readEoln();

        for (int j = 1; j < static_cast<int>(query.size()); ++j) {
            ensuref(query[j - 1] < query[j],
                    "query %d is not sorted or has repeated letters: %s",
                    i + 1, query.c_str());
        }

        ensuref(seen_queries.insert(query).second,
                "duplicate query at index %d: %s", i + 1, query.c_str());
    }

    inf.readEof();
}
