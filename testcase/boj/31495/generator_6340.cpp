#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
using namespace std;

string genWord(int minL = 1, int maxL = 5) {
    int L = rnd.next(minL, maxL);
    string w;
    for (int i = 0; i < L; i++) {
        char c = char('a' + rnd.next(0, 25));
        if (rnd.next(0, 1)) c = char(toupper(c));
        w.push_back(c);
    }
    return w;
}

string genContent(int minWords = 1, int maxWords = 3) {
    int W = rnd.next(minWords, maxWords);
    vector<string> ws;
    for (int i = 0; i < W; i++) {
        ws.push_back(genWord());
    }
    string s = ws[0];
    for (int i = 1; i < W; i++) {
        s += ' ';
        s += ws[i];
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a case type for diversity
    int t = rnd.next(0, 5);
    string S;

    if (t == 0) {
        // No quotes
        S = genContent(1, 3);
    } else if (t == 1) {
        // One quote at start
        S = "\"" + genContent(1, 3);
    } else if (t == 2) {
        // One quote at end
        S = genContent(1, 3) + "\"";
    } else if (t == 3) {
        // Two quotes empty inside
        S = "\"\"";
    } else if (t == 4) {
        // Two quotes with non-empty inside
        S = "\"" + genContent(1, 3) + "\"";
    } else {
        // Two quotes inside, wrong positions
        string c1 = genContent(1, 2);
        string c2 = genContent(1, 2);
        string c3 = genContent(1, 2);
        S = c1 + "\"" + c2 + "\"" + c3;
    }

    // Ensure length does not exceed 50
    if ((int)S.size() > 50) {
        S = S.substr(0, 50);
        // avoid cutting in middle of UTF, but our chars are single-byte
    }

    println(S);
    return 0;
}
