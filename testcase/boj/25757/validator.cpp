#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N and game type
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    // Single uppercase letter
    string g = inf.readToken("[A-Z]", "game_type");
    inf.readEoln();

    // Must be one of Y, F, O
    ensuref(g == "Y" || g == "F" || g == "O",
            "game_type must be one of 'Y', 'F', or 'O', got '%s'", g.c_str());

    // Next N lines: names (not necessarily unique, per statement + examples)
    for (int i = 0; i < N; ++i) {
        // Name: digits or English letters, length 1..20
        inf.readToken("[0-9A-Za-z]{1,20}", "name");
        inf.readEoln();
    }

    inf.readEof();
}
