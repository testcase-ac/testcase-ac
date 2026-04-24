#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    // We expect multiple lines, each at most 80 characters,
    // terminated by a line exactly "EOI". Maximum number of lines <= 100000.
    const int MAX_LINES = 100000;

    int lines = 0;
    while (true) {
        // Read a line of length between 0 and 80 (excluding the newline).
        // [^] matches any character (except newline, since readLine stops there).
        string s = inf.readLine("[^]{0,80}", "line");
        lines++;
        ensuref(lines <= MAX_LINES,
                "Too many lines: %d (maximum %d allowed)", lines, MAX_LINES);
        // If this is the terminator, stop reading further.
        if (s == "EOI") break;
    }
    // No extra content after the "EOI" line.
    inf.readEof();
    return 0;
}
