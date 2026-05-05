#include "testlib.h"
#include <set>
#include <string>
#include <vector>
#include <cctype>
#include <map>
#include <algorithm>
using namespace std;

// Helper: check if a string is a valid name (1-15 chars, a-z, A-Z, 0-9, hyphen)
bool is_valid_name(const string& s) {
    if (s.size() < 1 || s.size() > 15) return false;
    for (char c : s) {
        if (!(isalnum(c) || c == '-')) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    set<string> character_names;
    vector<string> names;
    vector<string> spoken_language;
    vector< set<string> > understood_languages;

    for (int i = 0; i < N; ++i) {
        string line = inf.readLine("[^]+", "character line");

        // Split line by spaces
        vector<string> tokens;
        size_t pos = 0, prev = 0;
        while ((pos = line.find(' ', prev)) != string::npos) {
            tokens.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }
        if (prev < line.size())
            tokens.push_back(line.substr(prev));

        ensuref(tokens.size() >= 2, "Line %d: Each character must have at least a name and a spoken language", i+1);
        ensuref(tokens.size() <= 22, "Line %d: Each character can have at most 1 spoken + 20 understood languages", i+1);

        string cname = tokens[0];
        ensuref(is_valid_name(cname), "Line %d: Invalid character name '%s'", i+1, cname.c_str());
        ensuref(character_names.count(cname) == 0, "Line %d: Duplicate character name '%s'", i+1, cname.c_str());
        character_names.insert(cname);
        names.push_back(cname);

        string lang_spoken = tokens[1];
        ensuref(is_valid_name(lang_spoken), "Line %d: Invalid spoken language name '%s'", i+1, lang_spoken.c_str());
        spoken_language.push_back(lang_spoken);

        set<string> langs;
        langs.insert(lang_spoken); // All characters understand the language they speak

        for (size_t j = 2; j < tokens.size(); ++j) {
            string lang = tokens[j];
            ensuref(is_valid_name(lang), "Line %d: Invalid understood language name '%s'", i+1, lang.c_str());
            langs.insert(lang);
        }
        understood_languages.push_back(langs);
    }

    inf.readEof();
}
