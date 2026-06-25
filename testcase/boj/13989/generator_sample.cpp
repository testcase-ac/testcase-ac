#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
using namespace std;

const int MAX_LINE = 120;

string capitalizedWord() {
    string s;
    s += char('A' + rnd.next(0, 25));
    int len = rnd.next(1, 9);
    for (int i = 0; i < len; ++i) {
        s += char('a' + rnd.next(0, 25));
    }
    return s;
}

string plainWord() {
    int mode = rnd.next(0, 4);
    string s;
    if (mode == 0) {
        int len = rnd.next(1, 9);
        for (int i = 0; i < len; ++i) s += char('a' + rnd.next(0, 25));
    } else if (mode == 1) {
        int len = rnd.next(2, 7);
        for (int i = 0; i < len; ++i) s += char('A' + rnd.next(0, 25));
    } else if (mode == 2) {
        s += char('A' + rnd.next(0, 25));
    } else if (mode == 3) {
        s += char('A' + rnd.next(0, 25));
        int lower = rnd.next(1, 4);
        for (int i = 0; i < lower; ++i) s += char('a' + rnd.next(0, 25));
        s += char('A' + rnd.next(0, 25));
    } else {
        int len = rnd.next(2, 7);
        s += char('a' + rnd.next(0, 25));
        for (int i = 1; i < len; ++i) {
            s += rnd.next(0, 1) ? char('a' + rnd.next(0, 25))
                                : char('A' + rnd.next(0, 25));
        }
    }
    return s;
}

string capSequence(int count) {
    string s = capitalizedWord();
    for (int i = 1; i < count; ++i) {
        s += ' ';
        s += capitalizedWord();
    }
    return s;
}

bool appendPiece(string& line, const string& piece) {
    if ((int)line.size() + (int)piece.size() > MAX_LINE) return false;
    line += piece;
    return true;
}

string randomLine(int mode) {
    string line;
    int target = rnd.next(25, 110);

    if (mode == 0) {
        line = capSequence(rnd.next(2, 7));
    } else if (mode == 1) {
        line = plainWord();
    } else if (mode == 2) {
        line = capSequence(rnd.next(2, 4));
        appendPiece(line, rnd.any(vector<string>{".", ","}));
    } else if (mode == 3) {
        line = capitalizedWord();
        appendPiece(line, "  ");
        appendPiece(line, capitalizedWord());
    } else {
        line = rnd.next(0, 1) ? capitalizedWord() : plainWord();
    }

    while ((int)line.size() < target) {
        vector<string> pieces;
        pieces.push_back(" " + capitalizedWord());
        pieces.push_back(" " + plainWord());
        pieces.push_back("  " + capitalizedWord());
        pieces.push_back("." + capitalizedWord());
        pieces.push_back("," + capitalizedWord());
        pieces.push_back(". " + plainWord());
        pieces.push_back(", " + capSequence(rnd.next(2, 4)));
        string piece = rnd.any(pieces);
        if (!appendPiece(line, piece)) break;
    }

    while (!line.empty() && line.back() == ' ') line.pop_back();
    if (line.empty()) line = plainWord();
    return line;
}

string nearLimitLine() {
    string line = capSequence(rnd.next(2, 5));
    while (true) {
        string piece = rnd.any(vector<string>{
            " " + capSequence(rnd.next(2, 4)),
            "  " + capitalizedWord(),
            "." + capitalizedWord(),
            "," + plainWord(),
            " " + plainWord(),
        });
        if ((int)line.size() + (int)piece.size() > MAX_LINE) break;
        line += piece;
    }
    while (!line.empty() && line.back() == ' ') line.pop_back();
    return line;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int lines = mode == 5 ? rnd.next(20, 80) : rnd.next(1, 8);
    vector<string> text;

    if (mode == 0) {
        text.push_back("A");
    } else if (mode == 1) {
        text.push_back(nearLimitLine());
    } else if (mode == 2) {
        text.push_back(capSequence(rnd.next(2, 6)));
        text.push_back(capitalizedWord() + "  " + capitalizedWord() + "." +
                       capSequence(rnd.next(2, 4)));
    } else {
        text.push_back(randomLine(mode));
    }

    while ((int)text.size() < lines) {
        int lineMode = rnd.next(0, 4);
        if (rnd.next(0, 5) == 0) {
            text.push_back(nearLimitLine());
        } else {
            text.push_back(randomLine(lineMode));
        }
    }

    for (const string& line : text) {
        println(line);
    }

    return 0;
}
