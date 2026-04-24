#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read board size N
    int N = inf.readInt(3, 50, "N");
    inf.readEoln();

    // Read N rows of the board
    vector<string> board(N);
    for (int i = 0; i < N; i++) {
        // Read the entire line, then validate length and characters
        string s = inf.readLine("[^]+", "row");
        ensuref((int)s.size() == N,
                "Row %d has incorrect length %d (expected %d)", i+1, (int)s.size(), N);
        for (int j = 0; j < N; j++) {
            char c = s[j];
            bool ok = (c == 'C' || c == 'P' || c == 'Z' || c == 'Y');
            ensuref(ok,
                    "Invalid character '%c' at row %d, column %d", c, i+1, j+1);
        }
        board[i] = s;
    }

    // Ensure there is at least one pair of adjacent cells with different colors
    bool foundDiff = false;
    for (int i = 0; i < N && !foundDiff; i++) {
        for (int j = 0; j < N && !foundDiff; j++) {
            if (j + 1 < N && board[i][j] != board[i][j+1]) {
                foundDiff = true;
            }
            if (i + 1 < N && board[i][j] != board[i+1][j]) {
                foundDiff = true;
            }
        }
    }
    ensuref(foundDiff,
            "No adjacent cells with different colors found");

    inf.readEof();
    return 0;
}
