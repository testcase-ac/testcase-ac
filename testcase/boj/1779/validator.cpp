#include "testlib.h"
#include <string>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of contractions and acronyms
    int C = inf.readInt(0, 49, "C");
    inf.readSpace();
    int A = inf.readInt(0, 49, "A");
    inf.readEoln();

    // Read C contraction mappings
    for (int i = 0; i < C; i++) {
        string s = inf.readLine("[^]*", "contraction_mapping");
        int n = (int)s.size();
        // Minimal valid mapping: "" -> "" has length 8
        ensuref(n >= 8, "Mapping line %d too short: '%s'", i+1, s.c_str());
        // Must start with a quote
        ensuref(s[0] == '"', "Mapping %d must start with '\"': '%s'", i+1, s.c_str());
        // Find end of first quoted string
        size_t p1 = s.find('"', 1);
        ensuref(p1 != string::npos, "Mapping %d missing closing '\"' for key: '%s'", i+1, s.c_str());
        // Content length <= 80
        int key_len = int(p1 - 1);
        ensuref(key_len <= 80, "Mapping %d key length %d exceeds 80", i+1, key_len);
        // After p1 must be " -> "
        ensuref(p1 + 4 < s.size(), "Mapping %d too short after key: '%s'", i+1, s.c_str());
        string arrow = s.substr(p1+1, 4);
        ensuref(arrow == " -> ", "Mapping %d must have ' -> ' after key: '%s'", i+1, s.c_str());
        // Then a quote
        size_t p2 = p1 + 5;
        ensuref(p2 < s.size() && s[p2] == '"', "Mapping %d missing opening '\"' for value: '%s'", i+1, s.c_str());
        // Find closing quote for value
        size_t p3 = s.find('"', p2+1);
        ensuref(p3 != string::npos, "Mapping %d missing closing '\"' for value: '%s'", i+1, s.c_str());
        // Must end exactly at p3
        ensuref(p3 == s.size() - 1, "Mapping %d has extra characters after value: '%s'", i+1, s.c_str());
        // Value length <= 80
        int val_len = int(p3 - (p2+1));
        ensuref(val_len <= 80, "Mapping %d value length %d exceeds 80", i+1, val_len);
    }

    // Read A acronym mappings
    for (int i = 0; i < A; i++) {
        string s = inf.readLine("[^]*", "acronym_mapping");
        int n = (int)s.size();
        ensuref(n >= 8, "Acronym mapping line %d too short: '%s'", i+1, s.c_str());
        ensuref(s[0] == '"', "Acronym mapping %d must start with '\"': '%s'", i+1, s.c_str());
        size_t p1 = s.find('"', 1);
        ensuref(p1 != string::npos, "Acronym mapping %d missing closing '\"' for key: '%s'", i+1, s.c_str());
        int key_len = int(p1 - 1);
        ensuref(key_len <= 80, "Acronym mapping %d key length %d exceeds 80", i+1, key_len);
        ensuref(p1 + 4 < s.size(), "Acronym mapping %d too short after key: '%s'", i+1, s.c_str());
        string arrow = s.substr(p1+1, 4);
        ensuref(arrow == " -> ", "Acronym mapping %d must have ' -> ' after key: '%s'", i+1, s.c_str());
        size_t p2 = p1 + 5;
        ensuref(p2 < s.size() && s[p2] == '"', "Acronym mapping %d missing opening '\"' for value: '%s'", i+1, s.c_str());
        size_t p3 = s.find('"', p2+1);
        ensuref(p3 != string::npos, "Acronym mapping %d missing closing '\"' for value: '%s'", i+1, s.c_str());
        ensuref(p3 == s.size() - 1, "Acronym mapping %d has extra characters after value: '%s'", i+1, s.c_str());
        int val_len = int(p3 - (p2+1));
        ensuref(val_len <= 80, "Acronym mapping %d value length %d exceeds 80", i+1, val_len);
    }

    // Read texts: each text is lines of <=80 chars, terminated by a line "#"
    int textCount = 0;
    while (true) {
        // Read one text until '#'
        while (true) {
            // Will error if EOF encountered before '#'
            string line = inf.readLine("[^]*", "text_line");
            ensuref((int)line.size() <= 80, "Text line too long (%d > 80): '%s'", (int)line.size(), line.c_str());
            if (line == "#") break;
        }
        textCount++;
        // After consuming the '#' line, check for EOF
        if (inf.eof()) break;
        // else continue to next text
    }
    ensuref(textCount > 0, "No text blocks found: missing terminating '#'");
    inf.readEof();
    return 0;
}
