#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We expect exactly 4 lines, each with exactly 4 characters in [A-O] or '.'
    vector<string> board(4);
    for (int i = 0; i < 4; i++) {
        // Build a variable name for clearer error messages
        string varName = "row_" + to_string(i + 1);
        board[i] = inf.readLine("[A-O\\.]{4}", varName);
    }

    // Count occurrences of each tile and the empty cell
    vector<int> cnt(256, 0);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            unsigned char c = board[i][j];
            cnt[c]++;
        }
    }

    // Each of A..O must appear exactly once
    for (char c = 'A'; c <= 'O'; c++) {
        ensuref(cnt[(unsigned char)c] == 1,
                "Tile '%c' appears %d times; expected exactly once",
                c, cnt[(unsigned char)c]);
    }
    // The empty cell '.' must appear exactly once
    ensuref(cnt[(unsigned char)'.'] == 1,
            "Empty cell '.' appears %d times; expected exactly once",
            cnt[(unsigned char)'.']);

    // No extra characters after the 4th line
    inf.readEof();
    return 0;
}
