#include "testlib.h"

#include <set>
#include <string>
#include <vector>
using namespace std;

namespace {

void ensureAsciiLine(const string& line, int minLen, int maxLen, const char* label) {
    ensuref((int)line.size() >= minLen, "%s is too short", label);
    ensuref((int)line.size() <= maxLen, "%s is too long: %d", label, (int)line.size());
    for (int i = 0; i < (int)line.size(); ++i) {
        unsigned char ch = line[i];
        ensuref(32 <= ch && ch <= 126, "%s has non-printable ASCII at column %d", label, i + 1);
    }
}

vector<string> splitByCommaSpace(const string& value) {
    vector<string> parts;
    size_t start = 0;
    while (true) {
        size_t pos = value.find(", ", start);
        if (pos == string::npos) {
            parts.push_back(value.substr(start));
            break;
        }
        parts.push_back(value.substr(start, pos - start));
        start = pos + 2;
    }
    return parts;
}

void ensureNameComponent(const string& component, const char* label) {
    ensuref(!component.empty(), "%s has an empty name component", label);
    ensuref(component.front() != ' ' && component.back() != ' ',
            "%s has leading or trailing space in a name component", label);
    for (char ch : component) {
        ensuref(ch != ',' && ch != ':', "%s has a comma or colon inside a name component", label);
    }
}

string validateName(const string& line, const char* label) {
    ensureAsciiLine(line, 1, 40, label);
    vector<string> parts = splitByCommaSpace(line);
    ensuref(parts.size() == 2, "%s must have exactly one comma-space separator", label);
    ensureNameComponent(parts[0], label);
    ensureNameComponent(parts[1], label);
    return line;
}

void validateTitle(const string& title) {
    ensureAsciiLine(title, 1, 250, "paper title");
    ensuref(title.front() != ' ' && title.back() != ' ', "paper title has leading or trailing space");
    for (char ch : title) {
        ensuref(ch != ',' && ch != ':', "paper title contains a comma or colon");
    }
}

vector<string> validatePaperLine(const string& line) {
    ensureAsciiLine(line, 1, 250, "paper line");

    size_t sep = line.find(": ");
    ensuref(sep != string::npos, "paper line is missing colon-space separator");
    ensuref(line.find(": ", sep + 2) == string::npos, "paper line has multiple colon-space separators");

    string authorsPart = line.substr(0, sep);
    string title = line.substr(sep + 2);
    validateTitle(title);

    vector<string> authorParts = splitByCommaSpace(authorsPart);
    ensuref(authorParts.size() >= 2 && authorParts.size() % 2 == 0,
            "paper line must contain one or more last-name, first-name author pairs");

    vector<string> authors;
    for (int i = 0; i < (int)authorParts.size(); i += 2) {
        ensureNameComponent(authorParts[i], "paper author");
        ensureNameComponent(authorParts[i + 1], "paper author");
        string author = authorParts[i] + ", " + authorParts[i + 1];
        ensuref((int)author.size() <= 40, "paper author name is too long: %s", author.c_str());
        authors.push_back(author);
    }
    return authors;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int scenario = 0;
    while (true) {
        int p = inf.readInt(0, 32000, "p");
        inf.readSpace();
        int n = inf.readInt(0, 3000, "n");
        inf.readEoln();

        if (p == 0 && n == 0) {
            break;
        }
        ensuref(p >= 1 && n >= 1, "scenario must have positive p and n unless it is the 0 0 terminator");

        ++scenario;
        setTestCase(scenario);

        set<string> authors;
        for (int i = 0; i < p; ++i) {
            string line = inf.readLine("[^]{1,250}", "paper");
            vector<string> paperAuthors = validatePaperLine(line);
            for (const string& author : paperAuthors) {
                authors.insert(author);
            }
        }

        for (int i = 0; i < n; ++i) {
            string name = inf.readLine("[^]{1,40}", "query_name");
            validateName(name, "query name");
        }

        ensuref((int)authors.size() <= 10000, "scenario has too many different authors: %d", (int)authors.size());
    }

    inf.readEof();
}
