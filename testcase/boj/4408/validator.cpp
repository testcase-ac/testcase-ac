#include "testlib.h"

#include <set>
#include <string>

using namespace std;

static string readNameLine(const char* fieldName) {
    string line = inf.readLine("[^]{1,80}", fieldName);

    ensuref(line.front() != ' ', "%s has leading blank", fieldName);
    ensuref(line.back() != ' ', "%s has trailing blank", fieldName);

    for (int i = 0; i < int(line.size()); ++i) {
        unsigned char ch = static_cast<unsigned char>(line[i]);
        ensuref(32 <= ch && ch <= 126,
                "%s contains non-printable ASCII at position %d", fieldName, i + 1);
        ensuref(i == 0 || line[i - 1] != ' ' || line[i] != ' ',
                "%s contains repeated blanks at positions %d and %d",
                fieldName, i, i + 1);
    }

    return line;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 20, "n");
    inf.readEoln();

    set<string> candidates;
    set<string> parties;

    for (int i = 0; i < n; ++i) {
        string candidate = readNameLine("candidate");
        ensuref(candidates.insert(candidate).second,
                "candidate name is repeated: %s", candidate.c_str());

        string party = readNameLine("party");
        if (party != "independent") {
            ensuref(parties.insert(party).second,
                    "party name is repeated: %s", party.c_str());
        }
    }

    int m = inf.readInt(1, 10000, "m");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        readNameLine("ballot");
    }

    inf.readEof();
}
