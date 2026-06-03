#include "testlib.h"

#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace {

vector<string> splitWords(const string& line) {
    stringstream ss(line);
    vector<string> words;
    string word;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}

void validateName(const string& name, const char* field) {
    ensuref(1 <= (int)name.size() && (int)name.size() <= 10,
            "%s length must be between 1 and 10: %s", field, name.c_str());
    for (char c : name) {
        ensuref('a' <= c && c <= 'z', "%s must contain only lowercase letters: %s",
                field, name.c_str());
    }
}

void validateOrdinarySpacing(const string& line, int lineIndex) {
    ensuref(!line.empty(), "preference line %d must not be empty", lineIndex);
    ensuref(line.front() != ' ', "preference line %d has leading space", lineIndex);
    ensuref(line.back() != ' ', "preference line %d has trailing space", lineIndex);
    ensuref(line.find("  ") == string::npos,
            "preference line %d has repeated spaces", lineIndex);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100, "n");
    inf.readEoln();

    vector<string> names(n);
    set<string> knownNames;
    for (int i = 0; i < n; ++i) {
        names[i] = inf.readToken("[a-z]{1,10}", "student_name");
        ensuref(knownNames.insert(names[i]).second, "duplicate student name: %s",
                names[i].c_str());
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    for (int i = 0; i < n; ++i) {
        string line = inf.readLine("[a-z\\ ]{1,1099}", "liked_students");
        validateOrdinarySpacing(line, i + 1);

        vector<string> liked = splitWords(line);
        ensuref(!liked.empty(), "student %s must like at least one student",
                names[i].c_str());

        set<string> seen;
        for (const string& name : liked) {
            validateName(name, "liked student name");
            ensuref(knownNames.count(name), "unknown liked student name for %s: %s",
                    names[i].c_str(), name.c_str());
            ensuref(name != names[i], "student %s cannot like themselves", names[i].c_str());
            // CHECK: The statement describes each row as a list of students liked by one
            // student. Treating duplicate names in one row as invalid preserves that set-like
            // meaning.
            ensuref(seen.insert(name).second,
                    "duplicate liked student name for %s: %s", names[i].c_str(), name.c_str());
        }
    }

    inf.readEof();
}
