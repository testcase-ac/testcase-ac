#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Prepare regex for each row: exactly M chars, each '1'-'9' or 'H'
    string pattern = "[1-9H]{" + to_string(M) + "}";

    // Read the board rows
    for (int i = 0; i < N; i++) {
        // row regex ensures exactly M characters, no spaces
        string row = inf.readToken(pattern, "row[" + to_string(i+1) + "]");
        inf.readEoln();

        // First cell must not be 'H'
        if (i == 0) {
            ensuref(row[0] != 'H',
                    "Top-left cell (1,1) must not be 'H', but found 'H'");
        }
    }

    // No extra content
    inf.readEof();
    return 0;
}
