#include "testlib.h"

#include <set>
#include <string>

using namespace std;

bool isAllowedNameChar(char c) {
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') ||
           ('0' <= c && c <= '9') || c == ' ';
}

void validateNameFormat(const string& name, const char* fieldName) {
    ensuref(!name.empty(), "%s must be nonempty", fieldName);
    ensuref((int)name.size() <= 100, "%s is too long: %d > 100",
            fieldName, (int)name.size());
    ensuref(name.front() != ' ', "%s has leading space", fieldName);
    ensuref(name.back() != ' ', "%s has trailing space", fieldName);

    for (int i = 0; i < (int)name.size(); ++i) {
        ensuref(isAllowedNameChar(name[i]),
                "%s has invalid character at position %d", fieldName, i + 1);
        ensuref(i == 0 || name[i] != ' ' || name[i - 1] != ' ',
                "%s has repeated spaces at positions %d and %d",
                fieldName, i, i + 1);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 20, "N");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int s = inf.readInt(2, 10, "S");
        inf.readEoln();

        set<string> engines;
        for (int i = 0; i < s; ++i) {
            string engine = inf.readLine("[^]{1,100}", "search_engine");
            validateNameFormat(engine, "search_engine");
            ensuref(engines.insert(engine).second,
                    "duplicate search engine name: %s", engine.c_str());
        }

        int q = inf.readInt(0, 100, "Q");
        inf.readEoln();

        for (int i = 0; i < q; ++i) {
            string query = inf.readLine("[^]{1,100}", "query");
            validateNameFormat(query, "query");
            ensuref(engines.count(query) != 0,
                    "query is not a search engine name: %s", query.c_str());
        }
    }

    inf.readEof();
}
