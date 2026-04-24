#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, L
    int N = inf.readInt(1, 300, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300, "M");
    inf.readSpace();
    int L = inf.readInt(1, 26, "L");
    inf.readEoln();

    // Read the word: uppercase letters only, length 1..50
    string word = inf.readToken("[A-Z]{1,50}", "word");
    inf.readEoln();

    // Read the grid: N lines, each of length exactly M, letters among first L ('A'..'A'+L-1)
    for (int i = 0; i < N; i++) {
        string row = inf.readLine("[A-Z]+", "grid_row");
        // check exact length
        ensuref((int)row.size() == M,
                "Row %d length is %d but should be %d", i+1, (int)row.size(), M);
        // check each character is within 'A'..'A'+L-1
        for (int j = 0; j < M; j++) {
            char c = row[j];
            ensuref(c >= 'A' && c < char('A' + L),
                    "Invalid character '%c' at row %d column %d; must be among first %d letters",
                    c, i+1, j+1, L);
        }
    }

    inf.readEof();
    return 0;
}
