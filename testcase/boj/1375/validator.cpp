#include "testlib.h"

#include <string>
#include <unordered_set>

using namespace std;

namespace {

constexpr int kMaxPeople = 1000000;
constexpr int kMaxComparisons = 1000000;
constexpr int kMaxQueries = 20;
constexpr int kMaxNameBytes = 6;

string readName(const char* name) {
    string value = inf.readToken("[^]+", name);
    ensuref(!value.empty(), "%s must not be empty", name);
    ensuref(static_cast<int>(value.size()) <= kMaxNameBytes,
            "%s is longer than %d bytes: %s", name, kMaxNameBytes, value.c_str());
    return value;
}

void rememberName(unordered_set<string>& names, const string& value, int n) {
    names.insert(value);
    ensuref(static_cast<int>(names.size()) <= n,
            "more distinct names appear than n: %d > %d",
            static_cast<int>(names.size()), n);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, kMaxPeople, "n");
    inf.readSpace();
    int m = inf.readInt(0, kMaxComparisons, "m");
    inf.readEoln();

    unordered_set<string> names;
    names.reserve(static_cast<size_t>(min(n, 2 * (m + kMaxQueries))) + 1);

    for (int i = 0; i < m; ++i) {
        string older = readName("older");
        inf.readSpace();
        string younger = readName("younger");
        inf.readEoln();

        ensuref(older != younger, "comparison %d uses the same person twice", i + 1);
        rememberName(names, older, n);
        rememberName(names, younger, n);
    }

    int q = inf.readInt(0, kMaxQueries, "q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        string first = readName("query_first");
        inf.readSpace();
        string second = readName("query_second");
        inf.readEoln();

        ensuref(first != second, "query %d uses the same person twice", i + 1);
        rememberName(names, first, n);
        rememberName(names, second, n);
    }

    inf.readEof();
}
