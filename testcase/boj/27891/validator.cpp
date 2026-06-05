#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

static string shifted(const string& name, int amount) {
    string result = name;
    for (char& ch : result) {
        ch = char('a' + (ch - 'a' + amount) % 26);
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const vector<string> prefixes = {
        "northlondo",
        "branksomeh",
        "koreainter",
        "stjohnsbur",
    };

    set<string> validNames;
    for (const string& prefix : prefixes) {
        for (int n = 0; n <= 25; ++n) {
            validNames.insert(shifted(prefix, n));
        }
    }

    string encrypted = inf.readToken("[a-z]{10}", "encrypted");
    inf.readEoln();
    ensuref(validNames.count(encrypted) != 0,
            "encrypted name is not generated from a listed school full name: %s",
            encrypted.c_str());
    inf.readEof();
}
