#include "testlib.h"
#include <map>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We expect exactly 8 lines, each with 3 color tokens among {B, G, O, R, W, Y}
    const string allowed = "BGORWY";
    string regex_color = string("[") + allowed + "]";

    map<char, int> cnt;
    for (int i = 0; i < 8; i++) {
        // Read three colors separated by single spaces, then end of line
        string s1 = inf.readToken(regex_color.c_str(), "color");
        inf.readSpace();
        string s2 = inf.readToken(regex_color.c_str(), "color");
        inf.readSpace();
        string s3 = inf.readToken(regex_color.c_str(), "color");
        inf.readEoln();

        // Count occurrences
        cnt[s1[0]]++;
        cnt[s2[0]]++;
        cnt[s3[0]]++;
    }

    // Each of the six colors must appear exactly 4 times (24 stickers total, 6 colors)
    for (char c : allowed) {
        int got = cnt[c];
        ensuref(got == 4, "Color '%c' appears %d times, but should appear exactly 4 times", c, got);
    }

    // No other colors should appear
    for (auto &p : cnt) {
        char c = p.first;
        if (allowed.find(c) == string::npos) {
            ensuref(false, "Invalid color '%c' found in input", c);
        }
    }

    inf.readEof();
    return 0;
}
