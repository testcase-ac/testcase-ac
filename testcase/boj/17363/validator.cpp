#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();

    // Allowed characters set
    auto isAllowed = [&](char c) {
        return c == '.' || c == 'O' || c == '-' || c == '|' ||
               c == '/' || c == '\\' || c == '^' ||
               c == '<' || c == 'v' || c == '>';
    };

    // Read each row
    for (int i = 0; i < N; i++) {
        // readToken stops at whitespace, so we ensure no spaces in the row
        string name = string("row_") + to_string(i+1);
        string row = inf.readToken("[^]+", name.c_str());
        // Check length
        ensuref((int)row.size() == M,
                "Length of %s is %d but expected %d", 
                name.c_str(), (int)row.size(), M);
        // Check each character
        for (int j = 0; j < M; j++) {
            char c = row[j];
            ensuref(isAllowed(c),
                    "Invalid character '%c' at row %d column %d", 
                    c, i+1, j+1);
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
