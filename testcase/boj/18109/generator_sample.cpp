#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string makeSyllable(bool preferFinal, bool preferCompoundFinal) {
    static const vector<string> initials = {
        "r", "R", "s", "e", "E", "f", "a", "q", "Q", "t",
        "T", "d", "w", "W", "c", "z", "x", "v", "g",
    };
    static const vector<string> vowels = {
        "k", "o", "i", "O", "j", "p", "u", "P", "h", "hk", "ho",
        "hl", "y", "n", "nj", "np", "nl", "b", "m", "ml", "l",
    };
    static const vector<string> simpleFinals = {
        "r", "R", "s", "e", "f", "a", "q", "t", "T", "d",
        "w", "c", "z", "x", "v", "g",
    };
    static const vector<string> compoundFinals = {
        "rt", "sw", "sg", "fr", "fa", "fq", "ft", "fx", "fv", "fg", "qt",
    };

    string final;
    if (preferCompoundFinal || (preferFinal && rnd.next(5) == 0)) {
        final = rnd.any(compoundFinals);
    } else if (preferFinal || rnd.next(3) != 0) {
        final = rnd.any(simpleFinals);
    }

    return rnd.any(initials) + rnd.any(vowels) + final;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int words = rnd.next(1, mode == 5 ? 10 : 5);
    vector<string> parts;

    for (int word = 0; word < words; ++word) {
        int syllables = rnd.next(1, mode == 5 ? 8 : 4);
        string part;
        for (int i = 0; i < syllables; ++i) {
            bool preferFinal = mode == 1 || mode == 2 || rnd.next(2) == 0;
            bool preferCompoundFinal = mode == 2 && rnd.next(2) == 0;
            part += makeSyllable(preferFinal, preferCompoundFinal);
        }
        parts.push_back(part);
    }

    string s = parts[0];
    for (int i = 1; i < int(parts.size()); ++i) {
        s += ' ';
        s += parts[i];
    }

    println(s);
    return 0;
}
