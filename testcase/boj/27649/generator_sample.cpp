#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomWord() {
    static const vector<string> words = {
        "grep", "echo", "expr", "cat", "cmd", "Makefile", "outfile", "infile",
        "VALUE_1", "X2", "$?", "$HOME", "a+b", "token_99"
    };
    string s = rnd.any(words);
    if (rnd.next(4) == 0) {
        s += rnd.any(string("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"));
    }
    return s;
}

string randomSpaces() {
    return string(rnd.next(1, 4), ' ');
}

string randomSeparator() {
    static const vector<string> separators = {"<", ">", "(", ")", "&&", "||"};
    string s = rnd.any(separators);
    if ((s == "&&" || s == "||") && rnd.next(5) == 0) {
        s += s;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int pieces = rnd.next(7, 24);
    string s;

    for (int i = 0; i < pieces; ++i) {
        if (!s.empty() && rnd.next(3) == 0) {
            s += randomSpaces();
        }

        if (mode == 0) {
            s += (rnd.next(5) == 0 ? randomSeparator() : randomWord());
        } else if (mode == 1) {
            s += (rnd.next(2) == 0 ? randomSeparator() : randomWord());
        } else if (mode == 2) {
            s += randomWord();
            if (rnd.next(4) != 0) {
                s += randomSpaces();
            }
        } else {
            s += (i % 2 == 0 ? randomWord() : randomSeparator());
        }
    }

    if (s.size() > 220) {
        s.resize(220);
        while (!s.empty() && (s.back() == '&' || s.back() == '|')) {
            s.pop_back();
        }
    }
    if (s.empty()) {
        s = "cmd";
    }

    println(s);
    return 0;
}
