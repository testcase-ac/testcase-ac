#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read board dimensions
    int R = inf.readInt(1, 100, "R");
    inf.readSpace();
    int C = inf.readInt(1, 100, "C");
    inf.readEoln();

    // Read the board and locate the player 'I'
    int cntI = 0;
    int start_r = -1, start_c = -1;
    for (int i = 0; i < R; i++) {
        // read a line with up to 100 chars, will check exact length below
        string row = inf.readLine("[.RI]{1,100}", "row");
        ensuref((int)row.size() == C,
                "Length of row %d must be %d, found %d", i+1, C, (int)row.size());
        for (int j = 0; j < C; j++) {
            char ch = row[j];
            ensuref(ch == '.' || ch == 'R' || ch == 'I',
                    "Invalid character at row %d, col %d: '%c'", i+1, j+1, ch);
            if (ch == 'I') {
                cntI++;
                start_r = i;
                start_c = j;
            }
        }
    }
    ensuref(cntI == 1,
            "Board must contain exactly one 'I', found %d", cntI);

    // Read move sequence (up to length 100, digits 1-9)
    string moves = inf.readLine("[1-9]{0,100}", "moves");

    // Directions mapping based on keypad:
    // 1:(+1,-1), 2:(+1,0), 3:(+1,+1)
    // 4:(0,-1), 5:(0,0), 6:(0,+1)
    // 7:(-1,-1),8:(-1,0),9:(-1,+1)
    static const int dr[10] = {0, 1, 1, 1, 0, 0, 0, -1, -1, -1};
    static const int dc[10] = {0, -1,0, 1, -1,0, 1, -1,  0,  1};

    // Simulate player moves to ensure none go off-board
    int r = start_r, c = start_c;
    for (int i = 0; i < (int)moves.size(); i++) {
        int d = moves[i] - '0';
        ensuref(1 <= d && d <= 9,
                "Invalid move character at index %d: '%c'", i+1, moves[i]);
        int nr = r + dr[d];
        int nc = c + dc[d];
        ensuref(0 <= nr && nr < R && 0 <= nc && nc < C,
                "Player moved out of board at move %d to (%d, %d)", i+1, nr, nc);
        r = nr; c = nc;
    }

    inf.readEof();
    return 0;
}
