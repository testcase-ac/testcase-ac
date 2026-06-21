#include "testlib.h"

#include <set>
#include <string>

using namespace std;

namespace {

string readEngineName(const string& fieldName) {
    string name = inf.readLine("[A-Za-z0-9\\ ]{1,100}", fieldName);

    ensuref(name.front() != ' ', "%s has leading space", fieldName.c_str());
    ensuref(name.back() != ' ', "%s has trailing space", fieldName.c_str());
    ensuref(name.find("  ") == string::npos, "%s has repeated spaces", fieldName.c_str());

    return name;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = inf.readInt(1, 20, "N");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= caseCount; ++caseIndex) {
        setTestCase(caseIndex);

        int engineCount = inf.readInt(2, 100, "S");
        inf.readEoln();

        set<string> engines;
        for (int i = 0; i < engineCount; ++i) {
            string engine = readEngineName("engine");
            ensuref(engines.insert(engine).second,
                    "duplicate search engine in case %d: %s",
                    caseIndex,
                    engine.c_str());
        }

        int queryCount = inf.readInt(0, 1000, "Q");
        inf.readEoln();

        for (int i = 0; i < queryCount; ++i) {
            string query = readEngineName("query");
            ensuref(engines.count(query) == 1,
                    "query %d in case %d is not a search engine name: %s",
                    i + 1,
                    caseIndex,
                    query.c_str());
        }
    }

    inf.readEof();
}
