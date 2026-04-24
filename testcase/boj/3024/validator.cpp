#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 30, "N");
    inf.readEoln();

    // Read board rows
    vector<string> board(N);
    for (int i = 0; i < N; i++) {
        // Read a line of length 1 to 30; we'll enforce exact N and valid chars manually
        string row = inf.readLine("[^]{1,30}", "row");
        ensuref((int)row.size() == N,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), N);
        for (int j = 0; j < N; j++) {
            char c = row[j];
            bool ok = (c == '.') || (c >= 'A' && c <= 'Z');
            ensuref(ok,
                    "Invalid character at row %d, col %d: '%c' (allowed: '.' or 'A'-'Z')",
                    i+1, j+1, c);
        }
        board[i] = row;
    }

    // Compute winners: any 3 identical non-dot chars in a row, column, or diagonal
    bool won[26] = {false};
    // Rows
    for (int i = 0; i < N; i++) {
        for (int j = 0; j + 2 < N; j++) {
            char c = board[i][j];
            if (c != '.' && board[i][j+1] == c && board[i][j+2] == c) {
                won[c - 'A'] = true;
            }
        }
    }
    // Columns
    for (int j = 0; j < N; j++) {
        for (int i = 0; i + 2 < N; i++) {
            char c = board[i][j];
            if (c != '.' && board[i+1][j] == c && board[i+2][j] == c) {
                won[c - 'A'] = true;
            }
        }
    }
    // Main diagonals
    for (int i = 0; i + 2 < N; i++) {
        for (int j = 0; j + 2 < N; j++) {
            char c = board[i][j];
            if (c != '.' && board[i+1][j+1] == c && board[i+2][j+2] == c) {
                won[c - 'A'] = true;
            }
        }
    }
    // Anti-diagonals
    for (int i = 0; i + 2 < N; i++) {
        for (int j = 2; j < N; j++) {
            char c = board[i][j];
            if (c != '.' && board[i+1][j-1] == c && board[i+2][j-2] == c) {
                won[c - 'A'] = true;
            }
        }
    }

    // Count distinct winners
    int cnt = 0;
    for (int k = 0; k < 26; k++) {
        if (won[k]) cnt++;
    }
    ensuref(cnt <= 1, "Multiple winners detected: %d", cnt);

    // Entire file should end here
    inf.readEof();
    return 0;
}
