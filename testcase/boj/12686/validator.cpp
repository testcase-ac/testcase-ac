#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int tc = 1; tc <= N; ++tc) {
        setTestCase(tc);

        // Read R and C
        int R = inf.readInt(1, 15, "R");
        inf.readSpace();
        int C = inf.readInt(1, 15, "C");
        inf.readEoln();

        vector<string> board;
        int king_count = 0;
        int king_r = -1, king_c = -1;
        for (int i = 0; i < R; ++i) {
            string row = inf.readLine("[.#K]{"+to_string(C)+","+to_string(C)+"}", "board row");
            ensuref((int)row.size() == C, "Row %d does not have exactly C=%d characters", i+1, C);
            for (int j = 0; j < C; ++j) {
                char ch = row[j];
                ensuref(ch == '.' || ch == '#' || ch == 'K', "Invalid character '%c' at row %d, col %d", ch, i+1, j+1);
                if (ch == 'K') {
                    king_count++;
                    king_r = i;
                    king_c = j;
                }
            }
            board.push_back(row);
        }
        ensuref(king_count == 1, "There must be exactly one 'K' on the board, found %d", king_count);

        // Ensure 'K' is not on a burned cell (redundant, but for clarity)
        ensuref(board[king_r][king_c] == 'K', "King position mismatch at (%d, %d)", king_r+1, king_c+1);

        // No extra blank line after each test case
        // (All R lines have been read, so next is either next test case or EOF)
    }

    inf.readEof();
}
