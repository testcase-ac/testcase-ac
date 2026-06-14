#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomLetters(int len, const string& alphabet) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const vector<string> words = {
        "A",       "Z",       "ABC",     "XYZ",      "LOREM",
        "IPSUM",   "DOLOR",   "CAESAR",  "SHIFT",    "QUESTION",
        "ANSWER",  "EXAM",    "PANIC",   "PROFESSOR"};

    string s;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int len = rnd.next(1, 30);
        s = randomLetters(len, alphabet);
    } else if (mode == 1) {
        int len = rnd.next(1, 80);
        char c = rnd.any(alphabet);
        s.assign(len, c);
    } else if (mode == 2) {
        int len = rnd.next(2, 80);
        char lo = rnd.any(string("ABCXYZ"));
        char hi = rnd.any(string("NOPQRS"));
        for (int i = 0; i < len; ++i) {
            s += (i % 2 == 0 ? lo : hi);
        }
    } else if (mode == 3) {
        int count = rnd.next(2, 8);
        for (int i = 0; i < count; ++i) {
            if (i > 0) s += ' ';
            if (rnd.next(0, 2) == 0) {
                s += rnd.any(words);
            } else {
                s += randomLetters(rnd.next(1, 10), alphabet);
            }
        }
    } else if (mode == 4) {
        int count = rnd.next(2, 20);
        for (int i = 0; i < count; ++i) {
            if (i > 0) s += ' ';
            s += rnd.any(alphabet);
        }
    } else {
        int len = rnd.next(900, 1000);
        s = randomLetters(len, alphabet);
    }

    println(s);
    return 0;
}
