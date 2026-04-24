#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read 7 lines of ASCII art
    vector<string> grid(7);
    const int MIN_WIDTH = 6*3 - 1;   // at least 3 characters: "a+b"
    const int MAX_WIDTH = 6*19 - 1;  // at most 19 pieces: 9 digits + '+' + 9 digits
    for (int i = 0; i < 7; i++) {
        grid[i] = inf.readLine("[^]+", "line");
        int w = (int)grid[i].size();
        ensuref(w >= MIN_WIDTH && w <= MAX_WIDTH,
                "Line %d has invalid width %d, expected between %d and %d", 
                i+1, w, MIN_WIDTH, MAX_WIDTH);
        // Check only '.' or 'x'
        for (int j = 0; j < w; j++) {
            char c = grid[i][j];
            ensuref(c == '.' || c == 'x',
                    "Invalid character '%c' at line %d, column %d; only '.' or 'x' allowed",
                    c, i+1, j+1);
        }
        // Check equal width
        if (i > 0) {
            ensuref(grid[i].size() == grid[0].size(),
                    "Line %d width %d does not match line 1 width %d",
                    i+1, (int)grid[i].size(), (int)grid[0].size());
        }
    }

    int W = (int)grid[0].size();
    // Must be of form 6*N - 1
    ensuref((W + 1) % 6 == 0,
            "Total width %d is not of form 6*N-1 for integer N", W);
    int N = (W + 1) / 6;
    ensuref(N >= 3 && N <= 19,
            "Number of characters N=%d derived from width is out of range [3,19]", N);

    // Define patterns for '0'..'9' and '+'
    vector<vector<string>> pats = {
        // '0'
        {"xxxxx",
         "x...x",
         "x...x",
         "x...x",
         "x...x",
         "x...x",
         "xxxxx"},
        // '1'
        {"....x",
         "....x",
         "....x",
         "....x",
         "....x",
         "....x",
         "....x"},
        // '2'
        {"xxxxx",
         "....x",
         "....x",
         "xxxxx",
         "x....",
         "x....",
         "xxxxx"},
        // '3'
        {"xxxxx",
         "....x",
         "....x",
         "xxxxx",
         "....x",
         "....x",
         "xxxxx"},
        // '4'
        {"x...x",
         "x...x",
         "x...x",
         "xxxxx",
         "....x",
         "....x",
         "....x"},
        // '5'
        {"xxxxx",
         "x....",
         "x....",
         "xxxxx",
         "....x",
         "....x",
         "xxxxx"},
        // '6'
        {"xxxxx",
         "x....",
         "x....",
         "xxxxx",
         "x...x",
         "x...x",
         "xxxxx"},
        // '7'
        {"xxxxx",
         "....x",
         "....x",
         "....x",
         "....x",
         "....x",
         "....x"},
        // '8'
        {"xxxxx",
         "x...x",
         "x...x",
         "xxxxx",
         "x...x",
         "x...x",
         "xxxxx"},
        // '9'
        {"xxxxx",
         "x...x",
         "x...x",
         "xxxxx",
         "....x",
         "....x",
         "xxxxx"},
        // '+'
        {".....",
         "..x..",
         "..x..",
         "xxxxx",
         "..x..",
         "..x..",
         "....."}
    };
    vector<char> pat_char = {'0','1','2','3','4','5','6','7','8','9','+'};

    // Check separator columns are dots
    for (int k = 1; k < N; k++) {
        int sep_col = k * 6 - 1;
        for (int r = 0; r < 7; r++) {
            ensuref(grid[r][sep_col] == '.',
                    "Separator column %d, row %d is '%c' but expected '.'",
                    sep_col+1, r+1, grid[r][sep_col]);
        }
    }

    // Extract each 7x5 block and map to character
    string expr;
    expr.reserve(N);
    for (int k = 0; k < N; k++) {
        vector<string> block(7);
        int start = k * 6;
        for (int r = 0; r < 7; r++) {
            block[r] = grid[r].substr(start, 5);
        }
        bool found = false;
        for (int p = 0; p < (int)pats.size(); p++) {
            if (block == pats[p]) {
                expr.push_back(pat_char[p]);
                found = true;
                break;
            }
        }
        ensuref(found, "Unrecognized character block at position %d", k+1);
    }

    // There must be exactly one '+' not at ends
    int plus_cnt = 0, plus_pos = -1;
    for (int i = 0; i < (int)expr.size(); i++) {
        if (expr[i] == '+') {
            plus_cnt++;
            plus_pos = i;
        }
    }
    ensuref(plus_cnt == 1, "Expected exactly one '+', found %d", plus_cnt);
    ensuref(plus_pos > 0 && plus_pos < N-1, "Plus '+' at invalid position %d", plus_pos+1);

    // Split into a and b
    string a = expr.substr(0, plus_pos);
    string b = expr.substr(plus_pos+1);
    auto check_num = [&](const string &s, const char *name){
        int L = (int)s.size();
        ensuref(L >= 1 && L <= 9, "%s length %d is out of bounds [1,9]", name, L);
        // No leading zeros, and positive => first char in '1'..'9'
        ensuref(s[0] >= '1' && s[0] <= '9',
                "%s has leading zero or is not positive: starts with '%c'", name, s[0]);
        for (int i = 1; i < L; i++) {
            ensuref(s[i] >= '0' && s[i] <= '9',
                    "%s contains invalid digit '%c' at position %d", name, s[i], i+1);
        }
    };
    check_num(a, "First integer a");
    check_num(b, "Second integer b");

    inf.readEof();
    return 0;
}
