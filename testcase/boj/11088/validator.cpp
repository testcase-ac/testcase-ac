#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

bool validName(const string& s) {
    if (s.empty() || s.size() > 15) {
        return false;
    }
    for (unsigned char c : s) {
        if (!isalnum(c) && c != '-') {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    set<string> character_names;
    for (int i = 0; i < n; ++i) {
        string line = inf.readLine("[^]+", format("character_%d", i + 1));

        ensuref(line.front() != ' ' && line.back() != ' ',
                "line %d has leading or trailing space", i + 1);
        ensuref(line.find("  ") == string::npos,
                "line %d has repeated spaces", i + 1);

        vector<string> tokens;
        size_t prev = 0;
        size_t pos = 0;
        while ((pos = line.find(' ', prev)) != string::npos) {
            tokens.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        tokens.push_back(line.substr(prev));

        ensuref(tokens.size() >= 2,
                "line %d must contain a character name and spoken language", i + 1);
        ensuref(tokens.size() <= 22,
                "line %d has more than 20 additional understood languages", i + 1);

        ensuref(validName(tokens[0]), "line %d has invalid character name '%s'",
                i + 1, tokens[0].c_str());
        ensuref(character_names.insert(tokens[0]).second,
                "duplicate character name '%s'", tokens[0].c_str());

        for (size_t j = 1; j < tokens.size(); ++j) {
            ensuref(validName(tokens[j]), "line %d has invalid language name '%s'",
                    i + 1, tokens[j].c_str());
        }
        for (size_t j = 2; j < tokens.size(); ++j) {
            ensuref(tokens[j] != tokens[1],
                    "line %d repeats spoken language '%s' as an additional language",
                    i + 1, tokens[j].c_str());
        }
    }

    inf.readEof();
}
