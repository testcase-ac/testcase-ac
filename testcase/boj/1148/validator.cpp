#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dictionary words until a line with single '-'
    string prev = "";
    int dict_cnt = 0;
    while (true) {
        string line = inf.readLine("[^]+", "dict_line");
        if (line == "-") {
            break;
        }
        // This is a dictionary word
        int idx = dict_cnt + 1;
        int len = (int)line.size();
        ensuref(len >= 4 && len <= 9,
                "Dictionary word %d has invalid length %d (expected 4..9): '%s'",
                idx, len, line.c_str());
        for (int i = 0; i < len; i++) {
            char c = line[i];
            ensuref(c >= 'A' && c <= 'Z',
                    "Dictionary word %d has invalid character '%c' at position %d: '%s'",
                    idx, c, i+1, line.c_str());
        }
        if (dict_cnt > 0) {
            ensuref(line >= prev,
                    "Dictionary not sorted at word %d: previous='%s', current='%s'",
                    idx, prev.c_str(), line.c_str());
        }
        prev = line;
        dict_cnt++;
        ensuref(dict_cnt <= 200000,
                "Number of dictionary words exceeds 200000 at word %d", dict_cnt);
    }

    // Read puzzle boards until a line with single '#'
    int puzzle_cnt = 0;
    while (true) {
        string line = inf.readLine("[^]+", "puzzle_line");
        if (line == "#") {
            break;
        }
        puzzle_cnt++;
        ensuref(puzzle_cnt <= 100000,
                "Number of puzzles exceeds 100000 at puzzle %d", puzzle_cnt);
        int len = (int)line.size();
        ensuref(len == 9,
                "Puzzle %d has invalid length %d (expected 9): '%s'",
                puzzle_cnt, len, line.c_str());
        for (int i = 0; i < 9; i++) {
            char c = line[i];
            ensuref(c >= 'A' && c <= 'Z',
                    "Puzzle %d has invalid character '%c' at position %d: '%s'",
                    puzzle_cnt, c, i+1, line.c_str());
        }
    }

    inf.readEof();
    return 0;
}
