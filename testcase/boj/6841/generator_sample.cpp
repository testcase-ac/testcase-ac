#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

namespace {
string randomUpperWord() {
    int len = rnd.next(1, 12);
    string s;
    for (int i = 0; i < len; ++i) {
        s += char('A' + rnd.next(26));
    }
    return s;
}

string randomSymbolWord() {
    const string symbols = "!#$%&()*+,-./:;<=>?@[\\]^_`{|}~";
    int len = rnd.next(1, 12);
    string s;
    for (int i = 0; i < len; ++i) {
        if (rnd.next(100) < 35) {
            s += char('A' + rnd.next(26));
        } else {
            s += rnd.any(symbols);
        }
    }
    return s;
}

string randomUnknown() {
    const vector<string> known = {
        "CU", ":-)", ":-(", ";-)", ":-P", "(~.~)", "TA", "CCC", "CUZ", "TY", "YW", "TTYL"};

    while (true) {
        string s = rnd.next(100) < 60 ? randomUpperWord() : randomSymbolWord();
        bool isKnown = false;
        for (const string& key : known) {
            if (s == key) {
                isKnown = true;
                break;
            }
        }
        if (!isKnown) {
            return s;
        }
    }
}
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<string> known = {
        "CU", ":-)", ":-(", ";-)", ":-P", "(~.~)", "TA", "CCC", "CUZ", "TY", "YW"};

    int mode = rnd.next(4);
    int linesBeforeTerminator;
    if (mode == 0) {
        linesBeforeTerminator = 0;
    } else if (mode == 1) {
        linesBeforeTerminator = rnd.next(1, 5);
    } else if (mode == 2) {
        linesBeforeTerminator = rnd.next(6, 20);
    } else {
        linesBeforeTerminator = rnd.next(21, 60);
    }

    for (int i = 0; i < linesBeforeTerminator; ++i) {
        int kind = rnd.next(100);
        if (kind < 45) {
            println(rnd.any(known));
        } else if (kind < 75) {
            println(randomUpperWord());
        } else {
            println(randomUnknown());
        }
    }
    println("TTYL");

    return 0;
}
