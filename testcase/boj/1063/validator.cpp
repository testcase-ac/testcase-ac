#include "testlib.h"
#include <string>
using namespace std;

bool isValidMove(const string &s) {
    return s == "R"  || s == "L"  || s == "B"  || s == "T" ||
           s == "RT" || s == "LT" || s == "RB" || s == "LB";
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: king position, stone position, N
    string king = inf.readToken("[A-H][1-8]", "king");
    inf.readSpace();
    string stone = inf.readToken("[A-H][1-8]", "stone");
    inf.readSpace();
    ensuref(king != stone, "King and stone cannot start at same location");
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Next N lines: each is one of the 8 possible move commands
    for (int i = 0; i < N; ++i) {
        string mv = inf.readToken("[A-Z]{1,2}", "move");
        inf.readEoln();
        ensuref(isValidMove(mv),
                "Invalid move command at line %d: '%s'", i + 2, mv.c_str());
    }

    inf.readEof();
}
