#include "testlib.h"

#include <set>
#include <string>

using namespace std;

bool isValidItemName(const string& name) {
    if (name.empty() || name.size() > 50) {
        return false;
    }
    if (name.front() == '_' || name.back() == '_') {
        return false;
    }

    bool previousWasSeparator = false;
    for (char c : name) {
        if (c == '_') {
            if (previousWasSeparator) {
                return false;
            }
            previousWasSeparator = true;
        } else if ('a' <= c && c <= 'z') {
            previousWasSeparator = false;
        } else {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    inf.readToken("[a-z]{1,50}", "s");
    inf.readEoln();

    set<string> itemNames;
    for (int i = 0; i < n; ++i) {
        string name = inf.readToken("[a-z_]{1,50}", "item_name");
        ensuref(isValidItemName(name), "invalid item name at index %d: %s", i + 1, name.c_str());
        ensuref(itemNames.insert(name).second, "duplicate item name at index %d: %s", i + 1, name.c_str());

        inf.readSpace();
        inf.readInt(1, 64, "quantity");
        inf.readEoln();
    }

    inf.readEof();
}
