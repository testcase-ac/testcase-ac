#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

namespace {

string readName(const string& fieldName) {
    return inf.readToken("[a-z0-9]{4,10}", fieldName);
}

vector<string> readNameLine(int count, const string& fieldPrefix) {
    vector<string> names;
    names.reserve(count);
    for (int i = 0; i < count; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        names.push_back(readName(fieldPrefix + "_" + to_string(i + 1)));
    }
    inf.readEoln();
    return names;
}

void ensureUniqueList(const vector<string>& names, const string& listName) {
    set<string> seen;
    for (int i = 0; i < static_cast<int>(names.size()); ++i) {
        ensuref(seen.insert(names[i]).second, "%s contains duplicate name at position %d: %s",
                listName.c_str(), i + 1, names[i].c_str());
    }
}

void readPreferenceRows(int n,
                        const set<string>& rowNames,
                        const set<string>& preferenceNames,
                        const string& rowKind,
                        const string& preferenceKind) {
    set<string> rowsSeen;

    for (int i = 0; i < n; ++i) {
        string owner = readName(rowKind + "_row_owner");
        ensuref(rowNames.count(owner) == 1, "%s preference row has unknown owner: %s",
                rowKind.c_str(), owner.c_str());
        ensuref(rowsSeen.insert(owner).second, "%s preference row repeated for owner: %s",
                rowKind.c_str(), owner.c_str());

        set<string> preferencesSeen;
        for (int j = 0; j < n; ++j) {
            inf.readSpace();
            string preferred = readName(rowKind + "_preference");
            ensuref(preferenceNames.count(preferred) == 1,
                    "%s preference row for %s has unknown %s name: %s",
                    rowKind.c_str(), owner.c_str(), preferenceKind.c_str(), preferred.c_str());
            ensuref(preferencesSeen.insert(preferred).second,
                    "%s preference row for %s repeats %s name: %s",
                    rowKind.c_str(), owner.c_str(), preferenceKind.c_str(), preferred.c_str());
        }
        inf.readEoln();
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "n");
    inf.readEoln();

    vector<string> men = readNameLine(n, "man_name");
    vector<string> women = readNameLine(n, "woman_name");

    ensureUniqueList(men, "men list");
    ensureUniqueList(women, "women list");

    set<string> menSet(men.begin(), men.end());
    set<string> womenSet(women.begin(), women.end());
    for (const string& man : men) {
        ensuref(womenSet.count(man) == 0, "name appears in both gender lists: %s", man.c_str());
    }

    readPreferenceRows(n, menSet, womenSet, "man", "woman");
    readPreferenceRows(n, womenSet, menSet, "woman", "man");

    inf.readEof();
}
