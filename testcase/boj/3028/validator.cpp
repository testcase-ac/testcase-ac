#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the sequence of moves: a single line containing only 'A', 'B', 'C', up to 50 characters.
    // We allow an empty sequence (0 mixes) up to 50 mixes.
    string s = inf.readLine("[ABC]{0,50}", "moves");
    // Just in case, double-check the length bound (though the regex enforces it).
    ensuref(s.size() <= 50, "Number of moves must be at most 50, but got %d", (int)s.size());

    // No extra lines or tokens: exactly one newline after the moves, then EOF.
    inf.readEof();
    return 0;
}
