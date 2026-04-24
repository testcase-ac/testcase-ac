#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read weight W: 1 < W <= 27
    int W = inf.readInt(2, 27, "W");
    inf.readEoln();

    // Read the flow graph string P (may contain spaces)
    string P = inf.readLine("[^]+", "P");

    // Check length constraint: length < 70000
    ensuref((int)P.size() < 70000,
            "Length of P must be less than 70000, but got %d", (int)P.size());

    // Allowed characters: uppercase letters, spaces, parentheses, brackets, commas
    for (int i = 0; i < (int)P.size(); i++) {
        char c = P[i];
        bool ok = false;
        if (c >= 'A' && c <= 'Z') ok = true;
        if (c == ' ' || c == '(' || c == ')' || c == '[' || c == ']' || c == ',') ok = true;
        ensuref(ok,
                "Invalid character in P at position %d: '%c'", i, c);
    }

    // End of file (no extra spaces or lines)
    inf.readEof();
    return 0;
}
