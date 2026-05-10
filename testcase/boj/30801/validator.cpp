#include "testlib.h"
#include <string>
#include <set>
#include <vector>
#include <map>
using namespace std;

// Valid directions for note line
const set<string> valid_directions = {
    "W", "A", "S", "D", "LU", "LD", "RU", "RD"
};

// Valid input keys for user input
const set<char> valid_input_keys = {
    'W', 'A', 'S', 'D', '8', '4', '2', '6', '7', '1', '9', '3'
};

// Helper: parse the note line and return the number of notes
vector<pair<string, bool>> parse_note_line(const string& line) {
    vector<pair<string, bool>> notes;
    int i = 0, n = line.size();
    while (i < n) {
        // Try to match 2-letter direction
        string dir;
        if (i+1 < n && (line.substr(i,2) == "LU" || line.substr(i,2) == "LD" || line.substr(i,2) == "RU" || line.substr(i,2) == "RD")) {
            dir = line.substr(i,2);
            i += 2;
        } else {
            dir = line.substr(i,1);
            i += 1;
        }
        ensuref(valid_directions.count(dir), "Invalid direction '%s' at position %d", dir.c_str(), i-(int)dir.size()+1);

        bool is_reverse = false;
        if (i < n && line[i] == '!') {
            is_reverse = true;
            i += 1;
        }
        notes.emplace_back(dir, is_reverse);
    }
    return notes;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1st line: note line
    string note_line = inf.readLine("[A-Z0-9!]{6,33}", "note_line");
    vector<pair<string, bool>> notes = parse_note_line(note_line);

    int lv = notes.size();
    ensuref(lv >= 6 && lv <= 11, "Number of notes (lv) must be between 6 and 11, got %d", lv);

    // 2nd line: user input
    string input_line = inf.readLine("[A-Z0-9]{1,20000}", "input_line");
    int input_len = input_line.size();
    ensuref(input_len >= 1 && input_len <= 20000, "Input length must be between 1 and 20000, got %d", input_len);

    for (int i = 0; i < input_len; ++i) {
        char c = input_line[i];
        ensuref(valid_input_keys.count(c), "Invalid input key '%c' at position %d", c, i+1);
    }

    inf.readEof();
}
