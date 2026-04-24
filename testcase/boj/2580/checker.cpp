#include "testlib.h"
#include <vector>

using namespace std;

static int given[9][9];          // Initial puzzle (0 = blank)

/*------------------------------------------------------------------
   Reads one 9 × 9 Sudoku grid from `stream`, verifies that it is a
   correct completion of the puzzle contained in `given`, and reports
   an appropriate verdict if it isn’t.

   If `stream` is `ans` (the jury’s file), every error ends with _fail.
   If `stream` is `ouf` (the contestant’s file), every error ends with _wa.
------------------------------------------------------------------*/
void readAndCheck(InStream &stream)
{
    int board[9][9];

    /* ----- 1. read the 81 integers ----------------------------- */
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            board[i][j] = stream.readInt(1, 9,
                format("board[%d][%d]", i + 1, j + 1).c_str());

    /* ----- 2. make sure no extra tokens are present ------------ */
    stream.skipBlanks();
    if (!stream.eof())
        stream.quitf(_wa, "extraneous data after 81 numbers");

    /* ----- 3. respect the original clues ----------------------- */
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (given[i][j] != 0 && board[i][j] != given[i][j])
                stream.quitf(_wa,
                    "cell (%d,%d) must be %d (found %d)",
                    i + 1, j + 1, given[i][j], board[i][j]);

    /* ----- 4. check rows, columns and 3 × 3 boxes -------------- */
    bool row[9][10] = {}, col[9][10] = {}, box[9][10] = {};

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j) {
            int v = board[i][j];
            int b = (i / 3) * 3 + (j / 3);     // box id 0..8

            if (row[i][v])  stream.quitf(_wa, "duplicate %d in row %d", v, i + 1);
            if (col[j][v])  stream.quitf(_wa, "duplicate %d in column %d", v, j + 1);
            if (box[b][v])  stream.quitf(_wa, "duplicate %d in 3x3 box (%d,%d)",
                                          v, b / 3 + 1, b % 3 + 1);

            row[i][v] = col[j][v] = box[b][v] = true;
        }
}

int main(int argc, char* argv[])
{
    registerTestlibCmd(argc, argv);

    /* ---------- read the original puzzle from `inf` ------------ */
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            given[i][j] = inf.readInt();

    /* ---------- verify jury answer (must always be valid) ------ */
    readAndCheck(ans);        // any failure → _fail

    /* ---------- verify contestant answer ----------------------- */
    readAndCheck(ouf);        // any failure → _wa

    /* ---------- everything is fine ----------------------------- */
    quitf(_ok, "valid Sudoku solution");
}
