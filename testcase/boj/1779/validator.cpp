#include "testlib.h"
#include <algorithm>
#include <set>
#include <string>
#include <vector>
using namespace std;

static string toUpperAscii(string s) {
    for (char& ch : s) {
        if ('a' <= ch && ch <= 'z') {
            ch = char(ch - 'a' + 'A');
        }
    }
    return s;
}

static string capitalizedVariant(string s) {
    if (!s.empty() && 'a' <= s[0] && s[0] <= 'z') {
        s[0] = char(s[0] - 'a' + 'A');
    }
    return s;
}

static pair<string, string> readMapping(const string& line, const string& kind, int index) {
    int n = (int)line.size();
    ensuref(n >= 8, "%s mapping line %d too short: '%s'", kind.c_str(), index, line.c_str());
    ensuref(line[0] == '"', "%s mapping %d must start with '\"': '%s'", kind.c_str(), index, line.c_str());

    size_t p1 = line.find('"', 1);
    ensuref(p1 != string::npos, "%s mapping %d missing closing '\"' for key: '%s'", kind.c_str(), index, line.c_str());
    int key_len = int(p1 - 1);
    ensuref(key_len >= 1, "%s mapping %d key must be non-empty", kind.c_str(), index);
    ensuref(key_len <= 80, "%s mapping %d key length %d exceeds 80", kind.c_str(), index, key_len);

    ensuref(p1 + 4 < line.size(), "%s mapping %d too short after key: '%s'", kind.c_str(), index, line.c_str());
    string arrow = line.substr(p1 + 1, 4);
    ensuref(arrow == " -> ", "%s mapping %d must have ' -> ' after key: '%s'", kind.c_str(), index, line.c_str());

    size_t p2 = p1 + 5;
    ensuref(p2 < line.size() && line[p2] == '"', "%s mapping %d missing opening '\"' for value: '%s'", kind.c_str(), index, line.c_str());

    size_t p3 = line.find('"', p2 + 1);
    ensuref(p3 != string::npos, "%s mapping %d missing closing '\"' for value: '%s'", kind.c_str(), index, line.c_str());
    ensuref(p3 == line.size() - 1, "%s mapping %d has extra characters after value: '%s'", kind.c_str(), index, line.c_str());

    int val_len = int(p3 - (p2 + 1));
    ensuref(val_len >= 1, "%s mapping %d expansion must be non-empty", kind.c_str(), index);
    ensuref(val_len <= 80, "%s mapping %d value length %d exceeds 80", kind.c_str(), index, val_len);

    return {line.substr(1, key_len), line.substr(p2 + 1, val_len)};
}

static bool crossesLineBoundary(const string& before, const string& after, const string& token) {
    if (token.size() < 2) {
        return false;
    }
    int max_left = min(before.size(), token.size() - 1);
    for (int left = 1; left <= max_left; ++left) {
        int right = (int)token.size() - left;
        if (right > (int)after.size()) {
            continue;
        }
        if (before.compare(before.size() - left, left, token, 0, left) == 0 &&
            after.compare(0, right, token, left, right) == 0) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int C = inf.readInt(0, 49, "C");
    inf.readSpace();
    int A = inf.readInt(0, 49, "A");
    inf.readEoln();

    set<string> splitSensitiveTokens;
    for (int i = 0; i < C; i++) {
        string line = inf.readLine("[^]*", "contraction_mapping");
        string key = readMapping(line, "Contraction", i + 1).first;
        splitSensitiveTokens.insert(key);
        splitSensitiveTokens.insert(toUpperAscii(key));
        splitSensitiveTokens.insert(capitalizedVariant(key));
    }

    for (int i = 0; i < A; i++) {
        string line = inf.readLine("[^]*", "acronym_mapping");
        splitSensitiveTokens.insert(readMapping(line, "Acronym", i + 1).first);
    }

    int textCount = 0;
    while (true) {
        string previousLine;
        bool hasPreviousLine = false;
        while (true) {
            string line = inf.readLine("[^]*", "text_line");
            ensuref((int)line.size() <= 80, "Text line too long (%d > 80): '%s'", (int)line.size(), line.c_str());
            if (line == "#") break;

            if (hasPreviousLine) {
                for (const string& token : splitSensitiveTokens) {
                    ensuref(!crossesLineBoundary(previousLine, line, token),
                            "Listed contraction or acronym '%s' is split across text lines", token.c_str());
                }
            }
            previousLine = line;
            hasPreviousLine = true;
        }
        textCount++;
        if (inf.eof()) break;
    }
    ensuref(textCount > 0, "No text blocks found: missing terminating '#'");
    inf.readEof();
    return 0;
}
